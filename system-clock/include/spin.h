#ifndef H__SPIN_
#define H__SPIN_

#include <stdint.h>

/*
 * Flash a code on the status LED.
 *
 * The flash codes a binary from MSB to LSB. A long flash is a 1, a short flash
 * is a 0. Each independent flashing is succeced by a break of 4 times that
 * of a long flash.
 */
void spin(uint8_t code);



#endif /* H__SPIN_ */
