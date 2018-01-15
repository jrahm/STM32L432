/*
 * This file sets the system clock to its full glory of 80Mhz
 */

#include "clock.h"
#include <stdint.h>

#define RCC_CR_HSERDY ((uint32_t)0x00020000) /* High-speed clock ready? */
#define RCC_CR_HSEON  ((uint32_t)0x00020000) /*!< External High Speed clock ready flag */

#define  FLASH_ACR_LATENCY ((uint32_t)0x00000001)        /*!< Latency */
#define  FLASH_ACR_PRFTEN  ((uint32_t)0x00000002)        /*!< Prefetch Buffer Enable */
#define  FLASH_ACR_ACC64   ((uint32_t)0x00000004)        /*!< Access 64 bits */

#define  RCC_APB1ENR_PWREN                   ((uint32_t)0x10000000)        /*!< Power interface clock enable */
#define  PWR_CR_VOS_0                        ((uint16_t)0x0800)     /*!< Bit 0 */

/*!< HPRE configuration */
#define  RCC_CFGR_HPRE_DIV1                  ((uint32_t)0x00000000)        /*!< SYSCLK not divided */
#define  RCC_CFGR_HPRE_DIV2                  ((uint32_t)0x00000080)        /*!< SYSCLK divided by 2 */
#define  RCC_CFGR_HPRE_DIV4                  ((uint32_t)0x00000090)        /*!< SYSCLK divided by 4 */
#define  RCC_CFGR_HPRE_DIV8                  ((uint32_t)0x000000A0)        /*!< SYSCLK divided by 8 */
#define  RCC_CFGR_HPRE_DIV16                 ((uint32_t)0x000000B0)        /*!< SYSCLK divided by 16 */
#define  RCC_CFGR_HPRE_DIV64                 ((uint32_t)0x000000C0)        /*!< SYSCLK divided by 64 */
#define  RCC_CFGR_HPRE_DIV128                ((uint32_t)0x000000D0)        /*!< SYSCLK divided by 128 */
#define  RCC_CFGR_HPRE_DIV256                ((uint32_t)0x000000E0)        /*!< SYSCLK divided by 256 */
#define  RCC_CFGR_HPRE_DIV512                ((uint32_t)0x000000F0)        /*!< SYSCLK divided by 512 */

#define  RCC_CFGR_PPRE1                      ((uint32_t)0x00000700)        /*!< PRE1[2:0] bits (APB1 prescaler) */
#define  RCC_CFGR_PPRE1_0                    ((uint32_t)0x00000100)        /*!< Bit 0 */
#define  RCC_CFGR_PPRE1_1                    ((uint32_t)0x00000200)        /*!< Bit 1 */
#define  RCC_CFGR_PPRE1_2                    ((uint32_t)0x00000400)        /*!< Bit 2 */

/*!< PPRE1 configuration */
#define  RCC_CFGR_PPRE1_DIV1                 ((uint32_t)0x00000000)        /*!< HCLK not divided */
#define  RCC_CFGR_PPRE1_DIV2                 ((uint32_t)0x00000400)        /*!< HCLK divided by 2 */
#define  RCC_CFGR_PPRE1_DIV4                 ((uint32_t)0x00000500)        /*!< HCLK divided by 4 */
#define  RCC_CFGR_PPRE1_DIV8                 ((uint32_t)0x00000600)        /*!< HCLK divided by 8 */
#define  RCC_CFGR_PPRE1_DIV16                ((uint32_t)0x00000700)        /*!< HCLK divided by 16 */

#define  RCC_CFGR_PPRE2                      ((uint32_t)0x00003800)        /*!< PRE2[2:0] bits (APB2 prescaler) */
#define  RCC_CFGR_PPRE2_0                    ((uint32_t)0x00000800)        /*!< Bit 0 */
#define  RCC_CFGR_PPRE2_1                    ((uint32_t)0x00001000)        /*!< Bit 1 */
#define  RCC_CFGR_PPRE2_2                    ((uint32_t)0x00002000)        /*!< Bit 2 */

/*!< PPRE2 configuration */
#define  RCC_CFGR_PPRE2_DIV1                 ((uint32_t)0x00000000)        /*!< HCLK not divided */
#define  RCC_CFGR_PPRE2_DIV2                 ((uint32_t)0x00002000)        /*!< HCLK divided by 2 */
#define  RCC_CFGR_PPRE2_DIV4                 ((uint32_t)0x00002800)        /*!< HCLK divided by 4 */
#define  RCC_CFGR_PPRE2_DIV8                 ((uint32_t)0x00003000)        /*!< HCLK divided by 8 */
#define  RCC_CFGR_PPRE2_DIV16                ((uint32_t)0x00003800)        /*!< HCLK divided by 16 */
#define  RCC_CFGR_PLLMUL                     ((uint32_t)0x003C0000)        /*!< PLLMUL[3:0] bits (PLL multiplication factor) */
#define  RCC_CFGR_PLLDIV                     ((uint32_t)0x00C00000)        /*!< PLLDIV[1:0] bits (PLL Output Division) */

#define  RCC_CFGR_PLLSRC                     ((uint32_t)0x00010000)        /*!< PLL entry clock source */
#define  RCC_CFGR_PLLSRC_HSE                 ((uint32_t)0x00010000)        /*!< HSE as PLL entry clock source */
#define  RCC_CFGR_PLLMUL8                    ((uint32_t)0x000C0000)        /*!< PLL input clock * 8 */
#define  RCC_CFGR_PLLDIV2                    ((uint32_t)0x00400000)        /*!< PLL clock output = CKVCO / 2 */
#define  RCC_CR_PLLON                        ((uint32_t)0x01000000)        /*!< PLL enable */
#define  RCC_CR_PLLRDY                       ((uint32_t)0x02000000)        /*!< PLL clock ready flag */
#define  RCC_CFGR_SW                         ((uint32_t)0x00000003)        /*!< SW[1:0] bits (System clock Switch) */
#define  RCC_CFGR_SW_PLL                     ((uint32_t)0x00000003)        /*!< PLL selected as system clock */
#define  RCC_CFGR_SWS                        ((uint32_t)0x0000000C)        /*!< SWS[1:0] bits (System Clock Switch Status) */
#define  RCC_CFGR_SWS_PLL                    ((uint32_t)0x0000000C)        /*!< PLL used as system clock */

inline int is_hse_ready()
{
  return RCC.cr & RCC_CR_HSERDY;
}

inline void hse_on()
{
  RCC.cr |= RCC_CR_HSEON;
}

#define TIMER 1000000
int set_sys_clock()
{
  uint32_t c = 0;  /* Time the PLL startup. */

  /* Turn on the HSE */
  hse_on();

  /* Wait 'til ready, or if it takes tool long, (c == TIMER). */
  for (c = 0; !is_hse_ready() && c < TIMER; ++ c);

  if (c == TIMER) {
    /* The HSE never came up. That's not cool! */
    return -1;
  }

  /* The HSE came up, now we just need to set it to be the main clock. */

  /* Don't really know why we're touching the flash registers ... */
  FLASH.acr |= FLASH_ACR_ACC64;   /* Enable 64-bit access. */
  FLASH.acr |= FLASH_ACR_PRFTEN;  /* Enable prefetch buffer. */
  FLASH.acr |= FLASH_ACR_LATENCY; /* Flash 1 wait state. */

  RCC.apb1enr |= RCC_APB1ENR_PWREN; /* Enable power. */
  PWR.cr = PWR_CR_VOS_0;            /* Set voltage to 1.8v. */

  /* Wait for the vwoltage regulator to turn on. */
  for (c = 0; (PWR.csr & PWR_CSR_VOSF) && c < TIMER; ++ c);

  if (c == TIMER) {
    /* Timeout occurred. */
    return -2;
  }

  RCC.cfgr |= RCC_CFGR_HPRE_DIV1;  /* HCLK = SYSCLK/1. */
  RCC.cfgr |= RCC_CFGR_PPRE2_DIV1; /* PCLK2 = HCLK/1 */
  RCC.cfgr |= RCC_CFGR_PPRE1_DIV1; /* PCLK1 = HCLK/1 */

  /* PLL Configuration */
  RCC.cfgr &= ~(
      RCC_CFGR_PLLSRC |
      RCC_CFGR_PLLMUL |
      RCC_CFGR_PLLDIV );

  RCC.cfgr |=
    RCC_CFGR_PLLSRC_HSE |
    RCC_CFGR_PLLMUL8    |
    RCC_CFGR_PLLDIV2;

  /* Enable the PLL. */
  RCC.cr |= RCC_CR_PLLON;

  /* Wait for PLL to become ready. */
  for(c = 0; !(RCC.cr & RCC_CR_PLLRDY) && c < TIMER; ++ c);

  if (c == TIMER) {
    /* Timeout occurred. */
    return -3;
  }

  /* Set PLL as the system clock. */
  RCC.cfgr &= ~RCC_CFGR_SW;
  RCC.cfgr |= RCC_CFGR_SW_PLL;

  /* Wait for PLL to be used as system clock. */
  for (c = 0; (RCC.cfgr & RCC_CFGR_SWS) != RCC_CFGR_SW_PLL && c < TIMER; ++ c);

  if (c == TIMER) {
    /* Timeout occurred. */
    return -4;
  }

  return 0;
}
