#include "gpio.h"
#include "delay.h"
#include "clock.h"
#include "spin.h"

volatile uint32_t delay_amt = 20000000 / 4;

/* Main function. This gets executed from the interrupt vector defined above. */
int main()
{
  /* Enable the GPIO port B. */

  __IO gpio_port_t* port_b = enable_gpio(GPIO_PORT_B);
  gpio_output_pin_t pin3 = set_gpio_pin_output(port_b, PIN_3);
  gpio_output_pin_t pin1 = set_gpio_pin_output(port_b, PIN_1);

  /* Enable a higher clock frequency. */
  set_system_clock_MHz(80);

  uint32_t count = 0;
  while(1) {
    /* Set the GPIO pin to high. */
    pin_off(pin1);
    pin_off(pin3);
    delay(delay_amt);

    /* Set the GPIO pin to low. */
    if (count % 4 == 0) {
      pin_on(pin1);
    }
    pin_on(pin3);
    delay(delay_amt);

    ++ count;
  }
}
