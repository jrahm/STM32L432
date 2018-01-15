#ifndef H__DELAY__
#define H__DELAY__

#include <stdint.h>

/*
 * Loops and count-downs the delay, the time this takes depends on the speed
 * of the clock.
 */
void delay(uint32_t delay);

#endif /* H__DELAY__ */
