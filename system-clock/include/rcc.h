#ifndef H__RCC_
#define H__RCC_

#include "common.h"

#define RCC_BASE ((uint32_t) 0x40021000)

typedef struct {
  __IO uint32_t c_r;       /* Clock control register. 0x00 */
  __IO uint32_t icsc_r;    /* Internal clock srcs calibration register. 0x04 */
  __IO uint32_t cfg_r;     /* clock confguration register. 0x08 */
  __IO uint32_t pllcfg_r;  /* PLL Configuration register. 0x0c */
  __IO uint32_t pllsai1cfg_r;  /* PLLSAI1 configuration register. 0x10 */

  __IO uint32_t reserved_1; /* Not used. offset 0x14. */

  __IO uint32_t cie_r;     /* Clock interrupt enable register. 0x18 */
  __IO uint32_t cif_r;     /* Clock interrupt flag regiseter.  0x1c */
  __IO uint32_t cic_r;     /* Clock interrupt clear register.  0x20 */

  __IO uint32_t reserved_2; /* Not used. offset 0x24. */

  __IO uint32_t ahb1rst_r;  /* AHB Peripheral 1 reset register. 0x28 */
  __IO uint32_t ahb2rst_r;  /* AHB Peripheral 2 reset register. 0x2c */
  __IO uint32_t ahb3rst_r;  /* AHB Peripheral 3 reset register. 0x30 */

  __IO uint32_t reserved_3; /* Not used. offset 0x34. */

  __IO uint32_t abp1rst1_r; /* APB Peripheral reset register 1. 0x38 */
  __IO uint32_t abp1rst2_r; /* APB Peripheral reset register 2. 0x3C */
  __IO uint32_t abp2rst_r;  /* APB Peripheral reset register.   0x40 */

  __IO uint32_t reserved_4; /* Not used. offset 0x44. */

  __IO uint32_t ahb1en_r;  /* AHB1 Peripheral enable register. 0x48 */
  __IO uint32_t ahb2en_r;  /* AHB2 Peripheral enable register. 0x4C */
  __IO uint32_t ahb3en_r;  /* AHB3 Peripheral enable register. 0x50 */

  __IO uint32_t reserved_5; /* Not used. offset 0x54. */

  __IO uint32_t apb1en1_r;  /* APB1 Peripheral enable register 1. 0x58 */
  __IO uint32_t apb1en2_r;  /* APB1 Peripheral enable register 2. 0x5C */
  __IO uint32_t apb2en_r;   /* APB2 Peripheral enable register.   0x60 */

  __IO uint32_t reserved_6; /* Not used. offset 0x64. */

  /* TODO add the rest starting at offset 0x68. */

} PACKED rcc_t;

#define RCC (*(__IO rcc_t*) RCC_BASE)

/* Macros to operate on the RCC registers. */

/* Sets the HSE. rcc is the RCC to use, e is zero for off, non-zero for on. */
#define set_hse(rcc, e) do \
{ \
  if (e) { \
    (rcc).c_r |= 1 << 16; \
  } else { \
    (rcc).c_r &= ~(1 << 16); \
  } \
} while(0)

/* Sets the HSI. rcc is the RCC to use, e is zero for off, non-zero for on. */
#define set_hsi(rcc, e) do \
{ \
  if (e) { \
    (rcc).c_r |= 1 << 8; \
  } else { \
    (rcc).c_r &= ~(1 << 8); \
  } \
} while(0)


/* Checks to see if the hse is ready. */
#define hse_ready(rcc) ((rcc).c_r & (1 << 17))

/* Checks to see if the hse is ready. */
#define hsi_ready(rcc) ((rcc).c_r & (1 << 10))

#endif
