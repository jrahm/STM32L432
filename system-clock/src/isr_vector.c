#include "isr_vector.h"
#include "gpio.h"
#include "delay.h"

/* Forward-declare the main function. This is implemented in main.c. */
void main();  

const void* vectors[] __attribute__((section(".vectors"))) = {
  (void *) 0x2000c000, /* Top of stack at top of sram1. 48k */
  main,                /* Reset handler */
  unhandled_isr,        /* NMI */
  unhandled_isr,        /* Hard Fault */
  unhandled_isr,        /* MemManage */
  unhandled_isr,        /* BusFault  */
  unhandled_isr,        /* UsageFault */
  unhandled_isr,        /* Reserved */ 
  unhandled_isr,        /* Reserved */
  unhandled_isr,        /* Reserved */
  unhandled_isr,        /* Reserved */
  unhandled_isr,        /* SVCall */
  unhandled_isr,        /* Debug */
  unhandled_isr,        /* Reserved */
  unhandled_isr,        /* PendSV */
  unhandled_isr,        /* SysTick */	

  /* External interrupt handlers follow */
  unhandled_isr,        /* 0 WWDG */
  unhandled_isr,        /* 1 PVD */
  unhandled_isr,        /* 2 TAMP_SAMP */
  unhandled_isr,        /* 3 RTC_WKUP */
  unhandled_isr,        /* 4 FLASH */
  unhandled_isr,        /* 5 RCC */
  unhandled_isr,        /* 6 EXTI0 */
  unhandled_isr,        /* 7 EXTI1 */
  unhandled_isr,        /* 8 EXTI2 */
  unhandled_isr,        /* 9 EXTI3 */
  unhandled_isr,        /* 10 EXTI4 */
  unhandled_isr,        /* 11 DMA_CH1 */
  unhandled_isr,        /* 12 DMA_CH2 */
  unhandled_isr,        /* 13 DMA_CH3 */
  unhandled_isr,        /* 14 DMA_CH4 */
  unhandled_isr,        /* 15 DMA_CH5 */
  unhandled_isr,        /* 16 DMA_CH6 */
  unhandled_isr,        /* 17 DMA_CH7 */
  unhandled_isr,        /* 18 ADC1 */
  unhandled_isr,        /* 19 CAN_TX */
  unhandled_isr,        /* 20 CAN_RX0 */
  unhandled_isr,        /* 21 CAN_RX1 */
  unhandled_isr,        /* 22 CAN_SCE */
  unhandled_isr,        /* 23 EXTI9_5 */
  unhandled_isr,        /* 24 TIM1_BRK/TIM15 */
  unhandled_isr,        /* 25 TIM1_UP/TIM16 */
  unhandled_isr,        /* 26 TIM1_TRG_COM */
  unhandled_isr,        /* 27 TIM1_CC */
  unhandled_isr,        /* 28 TIM2 */
  unhandled_isr,        /* 29 Reserved */
  unhandled_isr,        /* 30 Reserved */
  unhandled_isr,        /* 31 I2C1_EV */
  unhandled_isr,        /* 32 I2C1_ER */
  unhandled_isr,        /* 33 I2C2_EV */
  unhandled_isr,        /* 34 I2C2_ER */
  unhandled_isr,        /* 35 SPI1 */
  unhandled_isr,        /* 36 SPI2 */
  unhandled_isr,        /* 37 USART1 */
  unhandled_isr,        /* 38 USART2 */
  unhandled_isr,        /* 39 USART3 */
  unhandled_isr,        /* 40 EXTI15_10 */
  unhandled_isr,        /* 41 RTCAlarm */
  unhandled_isr,        /* 42 Reserved */
  unhandled_isr,        /* 43 Reserved */
  unhandled_isr,        /* 44 Reserved */
  unhandled_isr,        /* 45 Reserved */
  unhandled_isr,        /* 46 Reserved */
  unhandled_isr,        /* 47 Reserved */
  unhandled_isr,        /* 48 Reserved */
  unhandled_isr,        /* 49 SDMMC1 */
  unhandled_isr,        /* 50 Reserved */
  unhandled_isr,        /* 51 SPI3 */
  unhandled_isr,        /* 52 Reserved */
  unhandled_isr,        /* 53 Reserved */
  unhandled_isr,        /* 54 TIM6_DACUNDER */
  unhandled_isr,        /* 55 TIM7 */
  unhandled_isr,        /* 56 DMA2_CH1 */
  unhandled_isr,        /* 57 DMA2_CH2 */
  unhandled_isr,        /* 58 DMA2_CH3 */
  unhandled_isr,        /* 59 DMA2_CH4 */
  unhandled_isr,        /* 60 DMA2_CH5 */
  unhandled_isr,        /* 61 Reserved */
  unhandled_isr,        /* 62 Reserved */
  unhandled_isr,        /* 63 Reserved*/
  unhandled_isr,        /* 64 COMP */
  unhandled_isr,        /* 65 LPTIM1 */
  unhandled_isr,        /* 66 LPTIM2 */
  unhandled_isr,        /* 67 USB_FS */
  unhandled_isr,        /* 68 DMA_CH6 */
  unhandled_isr,        /* 69 DMA_CH7 */
  unhandled_isr,        /* 70 LPUART1 */
  unhandled_isr,        /* 71 QUADSPI */
  unhandled_isr,        /* 72 I2C3_EV */
  unhandled_isr,        /* 73 I2C3_ER */
  unhandled_isr,        /* 74 SAI1 */
  unhandled_isr,        /* 75 Reserved */
  unhandled_isr,        /* 76 SWPMI1 */
  unhandled_isr,        /* 77 TSC */
  unhandled_isr,        /* 78 Reserved */
  unhandled_isr,        /* 79 AES */
  unhandled_isr,        /* 80 RNG */
  unhandled_isr,        /* 81 FPU */
  unhandled_isr         /* 82 CRS */
};

/*
 * Does nothing ... forever.
 */
void unhandled_isr()
{
  __IO gpio_port_t* port_b = enable_gpio(GPIO_PORT_B);
  gpio_output_pin_t pin3 = set_gpio_pin_output(port_b, PIN_3);
  for(;;) {

    /* Flash in a distinct pattern to know that something went wrong. */

    pin_off(pin3);
    delay(100000);
    pin_on(pin3);
    delay(100000);
    pin_off(pin3);
    delay(100000);
    pin_on(pin3);
    delay(500000);
  }
}
