#include "gpio.h"

int main();

void spin();

/*
 * Interrupt service routine handlers.
 */
const void* vectors[] __attribute__((section(".vectors"))) = {
  (void *) 0x2000c000, /* Top of stack at top of sram1. 48k */
  main,                /* Reset handler */
  spin,        /* NMI */
  spin,        /* Hard Fault */
  spin,        /* MemManage */
  spin,        /* BusFault  */
  spin,        /* UsageFault */
  spin,        /* Reserved */ 
  spin,        /* Reserved */
  spin,        /* Reserved */
  spin,        /* Reserved */
  spin,        /* SVCall */
  spin,        /* Debug */
  spin,        /* Reserved */
  spin,        /* PendSV */
  spin,        /* SysTick */	

/* External interrupt handlers follow */
  spin,        /* 0 WWDG */
  spin,        /* 1 PVD */
  spin,        /* 2 TAMP_SAMP */
  spin,        /* 3 RTC_WKUP */
  spin,        /* 4 FLASH */
  spin,        /* 5 RCC */
  spin,        /* 6 EXTI0 */
  spin,        /* 7 EXTI1 */
  spin,        /* 8 EXTI2 */
  spin,        /* 9 EXTI3 */
  spin,        /* 10 EXTI4 */
  spin,        /* 11 DMA_CH1 */
  spin,        /* 12 DMA_CH2 */
  spin,        /* 13 DMA_CH3 */
  spin,        /* 14 DMA_CH4 */
  spin,        /* 15 DMA_CH5 */
  spin,        /* 16 DMA_CH6 */
  spin,        /* 17 DMA_CH7 */
  spin,        /* 18 ADC1 */
  spin,        /* 19 CAN_TX */
  spin,        /* 20 CAN_RX0 */
  spin,        /* 21 CAN_RX1 */
  spin,        /* 22 CAN_SCE */
  spin,        /* 23 EXTI9_5 */
  spin,        /* 24 TIM1_BRK/TIM15 */
  spin,        /* 25 TIM1_UP/TIM16 */
  spin,        /* 26 TIM1_TRG_COM */
  spin,        /* 27 TIM1_CC */
  spin,        /* 28 TIM2 */
  spin,        /* 29 Reserved */
  spin,        /* 30 Reserved */
  spin,        /* 31 I2C1_EV */
  spin,        /* 32 I2C1_ER */
  spin,        /* 33 I2C2_EV */
  spin,        /* 34 I2C2_ER */
  spin,        /* 35 SPI1 */
  spin,        /* 36 SPI2 */
  spin,        /* 37 USART1 */
  spin,        /* 38 USART2 */
  spin,        /* 39 USART3 */
  spin,        /* 40 EXTI15_10 */
  spin,        /* 41 RTCAlarm */
  spin,        /* 42 Reserved */
  spin,        /* 43 Reserved */
  spin,        /* 44 Reserved */
  spin,        /* 45 Reserved */
  spin,        /* 46 Reserved */
  spin,        /* 47 Reserved */
  spin,        /* 48 Reserved */
  spin,        /* 49 SDMMC1 */
  spin,        /* 50 Reserved */
  spin,        /* 51 SPI3 */
  spin,        /* 52 Reserved */
  spin,        /* 53 Reserved */
  spin,        /* 54 TIM6_DACUNDER */
  spin,        /* 55 TIM7 */
  spin,        /* 56 DMA2_CH1 */
  spin,        /* 57 DMA2_CH2 */
  spin,        /* 58 DMA2_CH3 */
  spin,        /* 59 DMA2_CH4 */
  spin,        /* 60 DMA2_CH5 */
  spin,        /* 61 Reserved */
  spin,        /* 62 Reserved */
  spin,        /* 63 Reserved*/
  spin,        /* 64 COMP */
  spin,        /* 65 LPTIM1 */
  spin,        /* 66 LPTIM2 */
  spin,        /* 67 USB_FS */
  spin,        /* 68 DMA_CH6 */
  spin,        /* 69 DMA_CH7 */
  spin,        /* 70 LPUART1 */
  spin,        /* 71 QUADSPI */
  spin,        /* 72 I2C3_EV */
  spin,        /* 73 I2C3_ER */
  spin,        /* 74 SAI1 */
  spin,        /* 75 Reserved */
  spin,        /* 76 SWPMI1 */
  spin,        /* 77 TSC */
  spin,        /* 78 Reserved */
  spin,        /* 79 AES */
  spin,        /* 80 RNG */
  spin,        /* 81 FPU */
  spin         /* 82 CRS */
};

/* Delay for some number of iterations. */
void delay(uint32_t itrs)
{
  /* Need to keep the compiler from optimizing this loop out entirely. */
  while(itrs --) {
    asm volatile ("");
  }
}

/* Main function. This gets executed from the interrupt vector defined above. */
int main()
{
  /* Enable the GPIO port B. */

  __IO gpio_port_t* port_b = enable_gpio(GPIO_PORT_B);
  gpio_output_pin_t pin3 = set_gpio_pin_output(port_b, PIN_3);
  gpio_output_pin_t pin1 = set_gpio_pin_output(port_b, PIN_1);

  while(1) {
    /* Set the GPIO pin to high. */
    pin_on(pin3);
    pin_off(pin1);
    delay(65535);
    delay(65535);
    delay(65535);
    delay(65535);
    delay(65535);
    delay(65535);
    delay(65535);
    delay(65535);
    delay(65535);
    delay(65535);

    /* Set the GPIO pin to low. */
    pin_off(pin3);
    pin_on(pin1);
    delay(65535);
    delay(65535);
    delay(65535);
    delay(65535);
    delay(65535);
    delay(65535);
    delay(65535);
    delay(65535);
    delay(65535);
    delay(65535);
  }
}

/*
 * Does nothing ... forever.
 */
void spin()
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
