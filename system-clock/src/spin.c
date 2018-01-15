#include "spin.h"
#include "gpio.h"
#include "delay.h"

#define SHORT_DELAY 200000
#define LONG_DELAY  (SHORT_DELAY * 2)

static void flash_bit(
    gpio_output_pin_t out_pin,
    uint8_t bit /* 0 => 0, non-zero => 1 */)
{
  pin_on(out_pin);
  if (bit) {
    delay(LONG_DELAY);
  } else {
    delay(SHORT_DELAY);
  }
  pin_off(out_pin);
  delay(SHORT_DELAY);
}

void spin(uint8_t c)
{
  uint8_t code;
  __IO gpio_port_t* port_b = enable_gpio(GPIO_PORT_B);
  gpio_output_pin_t pin3 = set_gpio_pin_output(port_b, PIN_3);

  for(;;) {
    code = c;
    flash_bit(pin3, code & 0x80);
    code <<= 1;
    flash_bit(pin3, code & 0x80);
    code <<= 1;
    flash_bit(pin3, code & 0x80);
    code <<= 1;
    flash_bit(pin3, code & 0x80);


    code <<= 1;
    flash_bit(pin3, code & 0x80);
    code <<= 1;
    flash_bit(pin3, code & 0x80);
    code <<= 1;
    flash_bit(pin3, code & 0x80);
    code <<= 1;
    flash_bit(pin3, code & 0x80);

    delay(LONG_DELAY * 4);
  }
}
