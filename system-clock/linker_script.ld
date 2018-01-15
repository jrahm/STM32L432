MEMORY
{
  flash : org = 0x08000000, len = 256k
}

SECTIONS
{
  /* This is where the code goes. */
  . = ORIGIN(flash);
  .text : {
    *(.vectors); /* All .vector sections go here. */
    *(.text);    /* All .text sections go here. */
  } >flash
}
