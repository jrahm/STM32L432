#define __IO volatile

#include <stdint.h>
#define RCC_BASE_2 0x40021000

int main();
void spin();

/*
 * Interrupt service routine handlers.
 */
const void* vectors[] __attribute__((section(".vectors"))) = {
    (void*)0x2000c000, /* Top of stack at top of sram1. 48k */
    main,              /* Reset handler */
    spin,              /* NMI */
    spin,              /* Hard Fault */
    spin,              /* MemManage */
    spin,              /* BusFault  */
    spin,              /* UsageFault */
    spin,              /* Reserved */
    spin,              /* Reserved */
    spin,              /* Reserved */
    spin,              /* Reserved */
    spin,              /* SVCall */
    spin,              /* Debug */
    spin,              /* Reserved */
    spin,              /* PendSV */
    spin,              /* SysTick */

    /* External interrupt handlers follow */
    spin, /* 0 WWDG */
    spin, /* 1 PVD */
    spin, /* 2 TAMP_SAMP */
    spin, /* 3 RTC_WKUP */
    spin, /* 4 FLASH */
    spin, /* 5 RCC */
    spin, /* 6 EXTI0 */
    spin, /* 7 EXTI1 */
    spin, /* 8 EXTI2 */
    spin, /* 9 EXTI3 */
    spin, /* 10 EXTI4 */
    spin, /* 11 DMA_CH1 */
    spin, /* 12 DMA_CH2 */
    spin, /* 13 DMA_CH3 */
    spin, /* 14 DMA_CH4 */
    spin, /* 15 DMA_CH5 */
    spin, /* 16 DMA_CH6 */
    spin, /* 17 DMA_CH7 */
    spin, /* 18 ADC1 */
    spin, /* 19 CAN_TX */
    spin, /* 20 CAN_RX0 */
    spin, /* 21 CAN_RX1 */
    spin, /* 22 CAN_SCE */
    spin, /* 23 EXTI9_5 */
    spin, /* 24 TIM1_BRK/TIM15 */
    spin, /* 25 TIM1_UP/TIM16 */
    spin, /* 26 TIM1_TRG_COM */
    spin, /* 27 TIM1_CC */
    spin, /* 28 TIM2 */
    spin, /* 29 Reserved */
    spin, /* 30 Reserved */
    spin, /* 31 I2C1_EV */
    spin, /* 32 I2C1_ER */
    spin, /* 33 I2C2_EV */
    spin, /* 34 I2C2_ER */
    spin, /* 35 SPI1 */
    spin, /* 36 SPI2 */
    spin, /* 37 USART1 */
    spin, /* 38 USART2 */
    spin, /* 39 USART3 */
    spin, /* 40 EXTI15_10 */
    spin, /* 41 RTCAlarm */
    spin, /* 42 Reserved */
    spin, /* 43 Reserved */
    spin, /* 44 Reserved */
    spin, /* 45 Reserved */
    spin, /* 46 Reserved */
    spin, /* 47 Reserved */
    spin, /* 48 Reserved */
    spin, /* 49 SDMMC1 */
    spin, /* 50 Reserved */
    spin, /* 51 SPI3 */
    spin, /* 52 Reserved */
    spin, /* 53 Reserved */
    spin, /* 54 TIM6_DACUNDER */
    spin, /* 55 TIM7 */
    spin, /* 56 DMA2_CH1 */
    spin, /* 57 DMA2_CH2 */
    spin, /* 58 DMA2_CH3 */
    spin, /* 59 DMA2_CH4 */
    spin, /* 60 DMA2_CH5 */
    spin, /* 61 Reserved */
    spin, /* 62 Reserved */
    spin, /* 63 Reserved*/
    spin, /* 64 COMP */
    spin, /* 65 LPTIM1 */
    spin, /* 66 LPTIM2 */
    spin, /* 67 USB_FS */
    spin, /* 68 DMA_CH6 */
    spin, /* 69 DMA_CH7 */
    spin, /* 70 LPUART1 */
    spin, /* 71 QUADSPI */
    spin, /* 72 I2C3_EV */
    spin, /* 73 I2C3_ER */
    spin, /* 74 SAI1 */
    spin, /* 75 Reserved */
    spin, /* 76 SWPMI1 */
    spin, /* 77 TSC */
    spin, /* 78 Reserved */
    spin, /* 79 AES */
    spin, /* 80 RNG */
    spin, /* 81 FPU */
    spin  /* 82 CRS */
};

typedef struct {
  __IO uint32_t value;
} rcc_reg_t;

#define RCC_AHB2ENR (*((__IO rcc_reg_t*)(RCC_BASE_2 + 0x4c)))

typedef enum {
  GPIO_PORT_A = 0,
  GPIO_PORT_B = 1,
  GPIO_PORT_C = 2,
  GPIO_PORT_D = 3
} gpio_port_number_t;

void enable_gpio(gpio_port_number_t port)
{
  RCC_AHB2ENR.value |= 1 << port;
}

typedef enum {
  PIN_0 = 0,
  PIN_1 = 1,
  PIN_2 = 2,
  PIN_3 = 3,
  PIN_4 = 4,
  PIN_5 = 5,
  PIN_6 = 6,
  PIN_7 = 7,
  PIN_8 = 8,
  PIN_9 = 9,
  PIN_10 = 10,
  PIN_11 = 11,
  PIN_12 = 12,
  PIN_13 = 13,
  PIN_14 = 14,
  PIN_15 = 15
} pin_t;

typedef enum {
  MODE_INPUT = 0,
  MODE_OUTPUT = 1,
  MODE_ALTERNATE = 2,
  MODE_ANALOG = 3
} pin_mode_t;

/* GPIO port speed. */
typedef enum {
  SPEED_2MHZ = 0,
  SPEED_10MHZ = 1,
  SPEED_50MHZ = 3,
} speed_t;

/*
 * Mode register. Input, output, alternate functiont or analog.
 */
typedef struct {
  __IO uint32_t value;
} __attribute__((packed)) mode_reg_t;

/*
 * Type register. Push/pull or open drain.
 */
typedef struct {
  __IO uint32_t value;
} __attribute__((packed)) type_reg_t;

/*
 * Speed register. Allows low, meduim, fast or high speed.
 */
typedef struct {
  __IO uint32_t value;
} __attribute__((packed)) speed_reg_t;

/*
 * Pull up/pull down register. Allows pull up, pull down, or no pull up or
 * pull down.
 */
typedef struct {
  __IO uint32_t value;
} __attribute__((packed)) pull_reg_t;

/*
 * Stores the data for reading from the outside.
 */
typedef struct {
  __IO uint32_t value;
} __attribute__((packed)) input_data_reg_t;

/*
 * Stores the data for writing to the outside.
 */
typedef struct {
  __IO uint32_t value;
} __attribute__((packed)) output_data_reg_t;

/*
 * Writing a 1 to a bit in this register allows the user to set or reset a bit
 * in the output data register.
 */
typedef struct {
  __IO uint32_t value;
} __attribute__((packed)) bit_set_reset_reg_t;

/*
 * Lock register. Allows the user to lock a pin so that its value cannot be
 * changed.
 */
typedef struct {
  __IO uint32_t value;
} __attribute__((packed)) lock_reg_t;

/*
 * Alternate function.
 */
typedef struct {
  __IO uint32_t value_high;
  __IO uint32_t value_low;
} __attribute__((packed)) alt_function_reg_t;

/* Structure defining the layout of a GPIO port on the STM32L432. */
typedef struct {
  __IO mode_reg_t mode;          /* Mode register */
  __IO pull_reg_t pupd;          /* Pull up/pull down/none register */
  __IO speed_reg_t speed;        /* Speed register */
  __IO type_reg_t type;          /* Type register */
  __IO input_data_reg_t input;   /* Input data register */
  __IO output_data_reg_t output; /* Output data register */
  __IO bit_set_reset_reg_t bsr;  /* Bit set/reset register */
  __IO lock_reg_t lock;          /* Lock register */
  __IO alt_function_reg_t altfn; /* Alternate function registers */
} __attribute__((packed)) gpio_port_t;

/*
 * Defines for GPIO memory mapped addresses.
 */
#define GPIO_A (*((__IO gpio_port_t*)0x48000000))
#define GPIO_B (*((__IO gpio_port_t*)0x48000400))
#define GPIO_C (*((__IO gpio_port_t*)0x48000800))

/*
 * Delays for `delay` iterations.
 */
void delay(uint32_t delay)
{
  while (delay--) {
    // Empty volatile assembly to keep the optimizer from getting
    // rid of this loop entirely.
    asm volatile("");
  }
}

/*
 * Sets the mode of a pin on a gpio port.
 *
 * gpio_port: the gpio port.
 * pin: the number of the port;
 * pin_mode: the mode of the pin. See pin_mode_t enum.
 */
void set_gpio_pin_mode(
    __IO gpio_port_t* gpio_port, uint32_t pin, pin_mode_t pin_mode)
{
  gpio_port->mode.value &= ~(0x03 << pin * 2);
  gpio_port->mode.value |= pin_mode << pin * 2;
}

/*
 * Sets the value on an output GPIO pin.
 *
 * gpio_port: The gpio port.
 * pin: the number of the pin to enable. Values 0-15
 * val: 0 to set the gpio pin to low, non-zero to set to high.
 */
void set_gpio_pin(__IO gpio_port_t* gpio_port, uint32_t pin, int val)
{
  if (val) {
    gpio_port->output.value |= 1 << pin;
  } else {
    gpio_port->output.value &= ~(1 << pin);
  }
}

/* Main function. This gets executed from the interrupt vector defined above. */
int main()
{
  /* Enable the GPIO port B. */
  enable_gpio(GPIO_PORT_B);

  /* Set pin 3 and pin 1 of GPIO_B to be an output pin. */
  set_gpio_pin_mode(&GPIO_B, /* pin = */ 3, MODE_OUTPUT);
  set_gpio_pin_mode(&GPIO_B, /* pin = */ 1, MODE_OUTPUT);

  while (1) {
    /* Set the GPIO pin to high. */
    set_gpio_pin(&GPIO_B, /* pin = */ 3, 1);
    set_gpio_pin(&GPIO_B, /* pin = */ 1, 0);
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
    set_gpio_pin(&GPIO_B, /* pin = */ 3, 0);
    set_gpio_pin(&GPIO_B, /* pin = */ 1, 1);
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
  for (;;) {
    /* Flash in a distinct pattern to know that something went wrong. */

    set_gpio_pin(&GPIO_B, /* pin = */ 3, 0);
    delay(100000);
    set_gpio_pin(&GPIO_B, /* pin = */ 3, 1);
    delay(100000);
    set_gpio_pin(&GPIO_B, /* pin = */ 3, 0);
    delay(100000);
    set_gpio_pin(&GPIO_B, /* pin = */ 3, 1);
    delay(500000);
  }
}
