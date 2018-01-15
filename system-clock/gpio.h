#ifndef GPIO_H__
#define GPIO_H__

#include "common.h"

#include <stdint.h>

/*
 * Possible GPIO ports.
 */
typedef enum {
  GPIO_PORT_A = 0,
  GPIO_PORT_B = 1,
  GPIO_PORT_C = 2,
  GPIO_PORT_D = 3
} gpio_port_number_t;

/*
 * Structure defining the layout of the layout of the GPIO registers on the
 * stm32l432 development board.
 */
typedef struct GPIO_PORT_STR {
  __IO uint32_t mode_r;   /* Mode register */
  __IO uint32_t pupd_r;   /* Pull up/pull down/none register */
  __IO uint32_t speed_r;  /* Speed register */
  __IO uint32_t type_r;   /* Type register */
  __IO uint32_t input_r;  /* Input data register */
  __IO uint32_t output_r; /* Output data register */
  __IO uint32_t bsr_r;    /* Bit set/reset register */
  __IO uint32_t lock_r;   /* Lock register */
  __IO uint32_t altfn_r;  /* Alternate function register */
} PACKED gpio_port_t;

/*
 * Enum defining the PINs in a GPIO port. Each port has 16 pins to use in
 * the stm32l432.
 */
typedef enum GPIO_PIN_ENUM {
  PIN_0  = 0,
  PIN_1  = 1,
  PIN_2  = 2,
  PIN_3  = 3,
  PIN_4  = 4,
  PIN_5  = 5,
  PIN_6  = 6,
  PIN_7  = 7,
  PIN_8  = 8,
  PIN_9  = 9,
  PIN_10 = 10,
  PIN_11 = 11,
  PIN_12 = 12,
  PIN_13 = 13,
  PIN_14 = 14,
  PIN_15 = 15
} gpio_pin_t;

/*
 * Enum defining the pin modes that are possible.
 */
typedef enum {
  MODE_INPUT     = 0,
  MODE_OUTPUT    = 1,
  MODE_ALTERNATE = 2,
  MODE_ANALOG    = 3
} gpio_pin_mode_t;

/*
 * Enum defining the pin speeds that are possible.
 */
typedef enum {
  SPEED_2MHZ = 0,
  SPEED_10MHZ = 1,
  SPEED_50MHZ = 3,
} speed_t;

/*
 * Structure defining an OUTPUT pin. Structurally equivalent to the input pin,
 * but can be used in a slightly type-safe manner.
 */
typedef struct {
  __IO gpio_port_t* gpio_port;
  gpio_pin_t pin;
} gpio_output_pin_t;

/*
 * Sets the mode on a GPIO pin.
 *
 * gpio_port: the gpio port to use.
 * pin: the pin number to set.
 * pin_mode: the mode to set the pin to.
 */
void set_gpio_pin_mode(
    __IO gpio_port_t* gpio_port,
    gpio_pin_t pin,
    gpio_pin_mode_t pin_mode);

/*
 * Sets the given GPIO pin to be an output pin. Returns an output_pin struct
 * corresponding to
 */
gpio_output_pin_t set_gpio_pin_output(
    __IO gpio_port_t* gpio_port,
    gpio_pin_t pin);

/*
 * Sets an output pin on or off.
 *
 * pin: the pin to toggle.
 * onoff: 0 for off, non-zero of on.
 */
void set_gpio_output_pin(
    gpio_output_pin_t pin,
    bool onoff);

#define pin_on(p) \
  set_gpio_output_pin(p, 1)

#define pin_off(p) \
  set_gpio_output_pin(p, 0)

/*
 * Enables a GPIO port and returns a reference to the register definition
 * of that GPIO port.
 */
__IO gpio_port_t* enable_gpio(gpio_port_number_t number);


#endif /* GPIO_H__ */
