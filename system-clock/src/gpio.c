#include "gpio.h"
#include "rcc.h"

/*
 * Sets the mode of a pin on a gpio por.
 */
void set_gpio_pin_mode(
    __IO gpio_port_t* gpio_port, gpio_pin_t pin, gpio_pin_mode_t mode)
{
  /* Each pin has a 2-bit mode provided at bits pin#*2 and pin#*2+1 */
  gpio_port->mode_r &= ~(0x03 << pin * 2);
  gpio_port->mode_r |= mode << pin * 2;
}

gpio_output_pin_t set_gpio_pin_output(
    __IO gpio_port_t* gpio_port, gpio_pin_t pin)
{
  set_gpio_pin_mode(gpio_port, pin, MODE_OUTPUT);

  return (gpio_output_pin_t){.gpio_port = gpio_port, .pin = pin};
}

void set_gpio_output_pin(gpio_output_pin_t pin, bool onoff)
{
  if (onoff) {
    pin.gpio_port->output_r |= 1 << pin.pin;
  } else {
    pin.gpio_port->output_r &= ~(1 << pin.pin);
  }
}

#define GPIO_PORTS_BASE_ADDR ((uint32_t)0x48000000)
__IO gpio_port_t* enable_gpio(gpio_port_number_t gpio_port_number)
{
  RCC.ahb2en_r |= 1 << gpio_port_number; /* Enable the GPIO port. */
  return (__IO gpio_port_t*)(GPIO_PORTS_BASE_ADDR + (gpio_port_number * 0x400));
}
