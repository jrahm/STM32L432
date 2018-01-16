Intro
-----

![The STM32L432](https://media.digikey.com/Photos/STMicro%20Photos/NUCLEO-L432KC.jpg)

This Project is a documentation of my journey trying to program the
STM32L432KCU6 Nucleo-32 (that would be [this
guy](https://www.digikey.com/product-detail/en/stmicroelectronics/NUCLEO-L432KC/497-16592-ND/6132763))
development board from BARE METAL. No operating system whatsoever. Not even an
RTOS. I will limit myself only to the standard C libraries and possibly future
libraries unrelated to the board itself (like maybe PCRE or OpenSSL, if such a
thing is even possible!).  The point of this exercise is to learn the ins and
outs of programming for a board at the lowest possible level!

These examples were developed on Linux, and work with Linux and GNU Make.
However, since none of the code depends on a platform, it should compile
on any system with a cross compiler.

Requirements
------------

* GNU Make
* st-flash -- This can be found [here](https://github.com/texane/stlink.git)
* perl
* Cross compiler for arm -- Mine is installed with prefix `arm-unknown-eabi-`.
