MEMORY
{
  flash : org = 0x08000000, len = 256k
  sram1 : org = 0x20000000, len = 48k
  sram2 : org = 0x10000000, len = 16k
}

SECTIONS
{
  /* This is where the code goes. */
  . = ORIGIN(flash);
  .text : {
    *(.vectors); /* All .vector sections go here. */
    *(.text);    /* All .text sections go here. */
  } >flash

  .data : {
    /* Data segment as defined in the flash. */
    INIT_DATA_VALUES = LOADADDR(.data);

    /* Data segment where it will be in memory. */
    DATA_SEGMENT_START = .;
    *(.data);
    DATA_SEGMENT_STOP = .;

    /* Align by 4 so we can optimize the copier to use uint32's. */
    . = ALIGN(0x04);
  } >sram1 AT>flash

  BSS_START = .;
  .bss : {
    *(.bss);
    . = ALIGN(0x04);
  } > sram1
  BSS_END = .;
}
