#ifndef CLOCK_H__
#define CLOCK_H__

#include <stdint.h>
#include "rcc.h"

#define PERIPH_BASE    ((uint32_t)       0x40000000)
#define AHBPERIPH_BASE (PERIPH_BASE +    0x00020000)
#define FLASH_R_BASE   (AHBPERIPH_BASE + 0x00003C00)
#define PWR_BASE       (PERIPH_BASE + 0x7000)
#define  PWR_CSR_VOSF                        ((uint16_t)0x0010)     /*!< Voltage Scaling select flag */


#ifndef __IO
#define __IO volatile
#endif

typedef struct {
  __IO uint32_t cr;
  __IO uint32_t csr;
} pwr_t;

// typedef struct {
//   __IO uint32_t acr;
//   __IO uint32_t pecr;
//   __IO uint32_t pdkeyr;
//   __IO uint32_t pekeyr;
//   __IO uint32_t prgkeyr;
//   __IO uint32_t optkeyr;
//   __IO uint32_t sr;
//   __IO uint32_t obr;
//   __IO uint32_t wrpr;       
// } flash_t;

// #define FLASH (*(flash_t*) (FLASH_R_BASE))
#define PWR (*(pwr_t*) (PWR_BASE))


/* Valid values for the PLLR/PLLQ bits of the PLLCFG register. */
typedef enum {
  PLL_DIVISOR_2   = 1,
  PLL_DIVISOR_4   = 3,
  PLL_DIVISOR_6   = 5,
  PLL_DIVISOR_8   = 7,
  PLL_DIVISOR_OFF = 0,
} pll_divisor_t;

/* Valid values for the PLLP bits off the PLLCFG register. */
typedef enum  {
  PLLP_DIVISOR_7   = 1,
  PLLP_DIVISOR_17  = 3,
  PLLP_DIVISOR_OFF = 0,
} pllp_divisor_t;

/* Valid values for the PLLM bits of the PLLCFG register. */
typedef enum {
  PLLM_DIVISOR_1 = 0,
  PLLM_DIVISOR_2 = 1,
  PLLM_DIVISOR_3 = 2,
  PLLM_DIVISOR_4 = 3,
  PLLM_DIVISOR_5 = 4,
  PLLM_DIVISOR_6 = 5,
  PLLM_DIVISOR_7 = 6,
  PLLM_DIVISOR_8 = 7,
} pllm_divisor_t;

/* Possible sources for the input clock. */
typedef enum {
  PLL_SRC_NONE = 0,
  PLL_SRC_MSI  = 1,
  PLL_SRC_HSI  = 2,
  PLL_SRC_HSE  = 3,
} pll_src_t;

/* Valid sources for the system clock. */
typedef enum {
  SYSTEM_CLOCK_SRC_MSI = 0,
  SYSTEM_CLOCK_SRC_HSI = 1,
  SYSTEM_CLOCK_SRC_HSE = 2,
  SYSTEM_CLOCK_SRC_PLL = 3,
} system_clock_src_t;

#define E_BADPLLN (-2)
#define E_BADPLLP_DIV (-1)
#define E_TIMEOUT (-3)
#define E_NOT_OFF (-4)
#define E_BAD_ARG (-5)

/*
 * Sets the system clock to a full 80Mhz.
 */
int set_system_clock_MHz(uint8_t mhz);

/*
 * Set the PLL on.
 */
int pll_on();

/*
 * Set the PLL off.
 */
int pll_off();

/*
 * Sets the source of the system clock.
 */
int set_system_clock_src(system_clock_src_t src);

/*
 * Configure the PLL.
 */
int configure_pll(
    uint8_t pllp_div_factor,
    pll_divisor_t  pllr,  /* System clock divisor. */
    pll_divisor_t  pllq,  /* Divison factor for PLL48M1CLK. */
    pllp_divisor_t pllp,  /* Divison factor for PLLSAI2CLK. */
    uint8_t        plln,  /* PLL numerator. */
    pllm_divisor_t pllm,  /* PLL denominator. */
    pll_src_t      pllsrc /* PLL source */ );

#endif /* CLOCK_H__ */
