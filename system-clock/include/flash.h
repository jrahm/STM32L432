#ifndef H__FLASH_
#define H__FLASH_

#include "common.h"

/*
 * Header file for dealing with flash.
 */

#define FLASH_BASE 0x40022000

typedef struct {
  __IO uint32_t ac_r; /* Flash access control register. */

  /* TODO fill out the rest. */
} PACKED flash_t;

#define FLASH (*(__IO flash_t*)FLASH_BASE)

#endif /* H__FLASH_ */
