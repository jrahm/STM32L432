#include "delay.h"

void delay(uint32_t delay)
{
  while (delay --) {
    /* needed to keep the compiler from optimizing away the loop. */
    asm volatile ("");
  }
}
