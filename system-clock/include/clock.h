#ifndef CLOCK_H__
#define CLOCK_H__

#include <stdint.h>

#define PERIPH_BASE    ((uint32_t)       0x40000000)
#define AHBPERIPH_BASE (PERIPH_BASE +    0x00020000)
#define RCC_BASE       (AHBPERIPH_BASE + 0x00001000)
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

typedef struct {
  __IO uint32_t acr;
  __IO uint32_t pecr;
  __IO uint32_t pdkeyr;
  __IO uint32_t pekeyr;
  __IO uint32_t prgkeyr;
  __IO uint32_t optkeyr;
  __IO uint32_t sr;
  __IO uint32_t obr;
  __IO uint32_t wrpr;       
} flash_t;

typedef struct {
  __IO uint32_t cr;
  __IO uint32_t icscr;
  __IO uint32_t cfgr;
  __IO uint32_t cir;
  __IO uint32_t ahbrstr;
  __IO uint32_t apb2rstr;
  __IO uint32_t apb1rstr;
  __IO uint32_t ahbenr;
  __IO uint32_t apb2enr;
  __IO uint32_t apb1enr;
  __IO uint32_t ahblpenr;
  __IO uint32_t apb2lpenr;
  __IO uint32_t apb1lpenr;      
  __IO uint32_t csr;    
} rcc_t;

#define RCC (*(rcc_t*) (RCC_BASE))
#define FLASH (*(flash_t*) (FLASH_R_BASE))
#define PWR (*(pwr_t*) (PWR_BASE))

/*
 * Sets the system clock to a full 80Mhz.
 */
int set_sys_clock();

#endif /* CLOCK_H__ */
