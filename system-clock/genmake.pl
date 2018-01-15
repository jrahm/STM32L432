#!/usr/bin/perl

# This script is designed to introspect C files and generate a makefile to use.

sub header_deps {
  my $file = @_[0];
  my @headers;

  if (open(my $fh, '<:encoding(UTF-8)', $file)) {
    print STDERR "\x1b[35m[Trace] - Reading file $file\x1b[00m\n";
    push(@headers, $file);

    while (<$fh>) {
      /#include\s+"(.*)"\s*$/ && push(@headers, header_deps($1));
    }
  }

  return @headers;
}

my @files = glob('./*.c');
my @obj_files;

open(my $fh, '<:encoding(UTF-8)', "Makefile.preamble") or die "Missing Makefile.preamble";
while (<$fh>) {
  print "$_";
}

foreach $file (@files) {
  (my $file_no_ext = $file) =~ s/^\.\/(.*)\.c$/\1/g;

  my $obj_file = "${file_no_ext}.o";
  my $c_file = "${file_no_ext}.c";
  my $s_file = "${file_no_ext}.s";

  push(@obj_files, $obj_file);
  my @deps = header_deps($c_file);

  my $deps_as_join = join(" ", @deps);

  # Emit the rule to make the object file.
  print "$obj_file: $deps_as_join\n\t";
  print '$(CC) -c ' . $c_file . ' -o ' . $obj_file . ' $(CFLAGS)' . "\n\n";

  # Emit the rule to make the assembly file.
  print "$s_file: $deps_as_join\n\t";
  print '$(CC) -S ' . $c_file . ' -o ' . $s_file . ' $(CFLAGS)' . "\n\n";
}

my $obj_files_deps = join(' ', @obj_files);
print "main.elf: $obj_files_deps linker_script.ld\n\t";
print '$(LD) -o main.elf $(LD_FLAGS) ' . "$obj_files_deps\n\n";
