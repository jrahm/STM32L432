/*
 * This file sets the system clock to its full glory of 80Mhz
 */

#include "clock.h"
#include "gpio.h"
#include "spin.h"
#include "flash.h"
#include <stdint.h>

#define TIMEOUT 10000

int pll_off()
{
  uint32_t c;

  RCC.c_r &= ~BIT(24); /* Turn off pll. */
  for(c = 0; c < TIMEOUT && RCC.c_r & BIT(25); ++ c); /* Wait for OFF. */
  
  if (c == TIMEOUT) {
    return E_TIMEOUT;
  }

  return 0;
}

int pll_on()
{
  uint32_t c;

  RCC.c_r |= BIT(24); /* Turn on PLL. */
  for(c = 0; c < TIMEOUT && !(RCC.c_r & BIT(25)); ++ c); /* Wait for RDY. */

  if (c == TIMEOUT) {
    return E_TIMEOUT;
  }

  return 0;
}

int configure_pll(
    uint8_t pllp_div_factor,
    pll_divisor_t  pllr,  /* System clock divisor. */
    pll_divisor_t  pllq,  /* Divison factor for PLL48M1CLK. */
    pllp_divisor_t pllp,  /* Divison factor for PLLSAI2CLK. */
    uint8_t        plln,  /* PLL numerator. */
    pllm_divisor_t pllm,  /* PLL denominator. */
    pll_src_t      pllsrc /* PLL source */ )
{
  if (RCC.c_r & BIT(25)) {
    /* PLL must be off to configure it. */
    return E_NOT_OFF;
  }

  /* Make sure inputs are valid. */
  if (pllp_div_factor == 1 || pllp_div_factor > 31) {
    return E_BADPLLP_DIV;
  }
  if (plln < 8 || plln > 86) {
    return E_BADPLLN;
  }

  RCC.pllcfg_r =
    (pllp_div_factor << 27) |
    (pllr << 24) |
    (pllq << 20) |
    (pllp << 16) |
    (plln << 8)  |
    (pllm << 4)  |
    (pllsrc << 0);

  return 0;
}
  
int set_system_clock_MHz(uint8_t mhz)
{
  /* Set the source of the system colck to MSI temporarily. */
  set_system_clock_src(SYSTEM_CLOCK_SRC_MSI);

  if (mhz <= 8 || mhz > 80) {
    return E_BAD_ARG;
  }

  pll_off();

  configure_pll(
    0 /* pllp_div_factor */,
    PLL_DIVISOR_4  /* pllr: VCO / 4 = mhz MHz. */,
    PLL_DIVISOR_4  /* pllq: VCO / 4 = mhz MHz */,
    PLLP_DIVISOR_7 /* pllp */,

    /* The following set the frequency of VCO to (mhz*4)MHz: mhz * 1 * 4MHz. */
    mhz            /* plln    | mhz */,
    PLLM_DIVISOR_1 /* pllm    | 01 */,
    PLL_SRC_MSI    /* pll src | 04 Mhz */);

  pll_on();

  /* Configure the flash to have 4 wait states. This is required at
   * 80 MHz. */
  FLASH.ac_r &= ~0x07;
  FLASH.ac_r |= 0x04;

  /* Set the source of the system colck to PLL. */
  set_system_clock_src(SYSTEM_CLOCK_SRC_PLL);
  return 0;
}

int set_system_clock_src(system_clock_src_t src)
{
  uint8_t value = RCC.cfg_r & ~0x03;
  RCC.cfg_r = value | src;
}
