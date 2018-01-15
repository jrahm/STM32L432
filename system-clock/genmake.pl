#!/usr/bin/perl

# This script is designed to introspect C files and generate a makefile to use.

sub header_deps {
  my $file = @_[0];
  my @headers;

  if (open(my $fh, '<:encoding(UTF-8)', $file)) {
    print STDERR "\x1b[35m[Trace] - Reading file $file\x1b[00m\n";
    push(@headers, $file);

    while (<$fh>) {
      /#include\s+"(.*)"\s*$/ && push(@headers, header_deps("include/$1"));
    }
  }

  return @headers;
}

my @files = glob('src/*.c');
my @obj_files;

open(my $fh, '<:encoding(UTF-8)', "Makefile.preamble")
    or die "Missing Makefile.preamble";

while (<$fh>) {
  print "$_";
}

# Emit a rule that will rerun genmake if the c files do not match.
my $idempotency_cmd =
    "ls src/*.c include/*.h| sha1sum | awk '{print \$1}'";

my $idempotency_cmd_make =
    "ls src/*.c include/*.h | sha1sum | awk '{print \$\$1}'";

print "IDEMPOTENCY_HASH=" . `$idempotency_cmd` . "\n";

my $arch_obs_dir = "_\$(PREFIX)_obs";
print "$arch_obs_dir:\n\t";
print "mkdir $arch_obs_dir\n";

foreach $file (@files) {
  my $c_file = $file;
  (my $file_no_ext = $file) =~ s/src\/(.*)\.c$/\1/g;

  my $obj_file = "$arch_obs_dir/${file_no_ext}.o";
  my $s_file = "${file_no_ext}.s";

  push(@obj_files, $obj_file);
  my @deps = header_deps($c_file);

  my $deps_as_join = join(" ", @deps);

  # Emit the rule to make the object file.
  print "$obj_file: $arch_obs_dir $deps_as_join\n\t";
  print '$(CC) -c ' . $c_file . ' -o ' . $obj_file . ' $(CFLAGS)' . "\n\n";

  # Emit the rule to make the assembly file.
  print "$s_file: $deps_as_join\n\t";
  print '$(CC) -S ' . $c_file . ' -o ' . $s_file . ' $(CFLAGS)' . "\n\n";
}

my $obj_files_deps = join(' ', @obj_files);
print "FORCE:\n\t\n\n";
print "$arch_obs_dir/main.elf: FORCE $obj_files_deps linker/linker_script.ld\n\t";
print "([ \"\$\$($idempotency_cmd_make)\" != \"\$(IDEMPOTENCY_HASH)\" ] "
        . "&& ./genmake.pl > Makefile && make main.elf ) "
        . "|| "
        . "\$(LD) -o $arch_obs_dir/main.elf \$(LD_FLAGS) $obj_files_deps\n\n";
