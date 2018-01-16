#include "spin.h"
#include "delay.h"
#include "gpio.h"

#define SHORT_DELAY 200000
#define LONG_DELAY (SHORT_DELAY * 2)

static void flash_bit(
    uint32_t base, gpio_output_pin_t out_pin,
    uint8_t bit /* 0 => 0, non-zero => 1 */)
{
  pin_on(out_pin);
  if (bit) {
    delay(base * 2);
  } else {
    delay(base);
  }
  pin_off(out_pin);
  delay(base);
}

void spin(uint32_t base, uint8_t c)
{
  uint8_t code;
  __IO gpio_port_t* port_b = enable_gpio(GPIO_PORT_B);
  gpio_output_pin_t pin3 = set_gpio_pin_output(port_b, PIN_3);

  for (;;) {
    code = c;
    flash_bit(base, pin3, code & 0x80);
    code <<= 1;
    flash_bit(base, pin3, code & 0x80);
    code <<= 1;
    flash_bit(base, pin3, code & 0x80);
    code <<= 1;
    flash_bit(base, pin3, code & 0x80);

    code <<= 1;
    flash_bit(base, pin3, code & 0x80);
    code <<= 1;
    flash_bit(base, pin3, code & 0x80);
    code <<= 1;
    flash_bit(base, pin3, code & 0x80);
    code <<= 1;
    flash_bit(base, pin3, code & 0x80);

    delay(base * 4);
  }
}
