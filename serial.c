#include <stdlib.h>

#include "hardware/i2c.h"
#include "inc/font.h"
#include "inc/ssd1306.h"
#include "pico/stdlib.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15

ssd1306_t ssd;

void config_serial() {
  // I2C Initialisation. Using it at 400Khz.
  i2c_init(I2C_PORT, 400 * 1000);
  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(I2C_SCL);
  ssd1306_init(&ssd, WIDTH, HEIGHT, false, 0x3C, I2C_PORT);
  ssd1306_config(&ssd);
  ssd1306_send_data(&ssd);
  ssd1306_fill(&ssd, false);
  ssd1306_rect(&ssd, 3, 3, 122, 58, false, true);
}

void print_serial(char *text) {
  ssd1306_draw_string(&ssd, text, 8, 10);
  ssd1306_send_data(&ssd);
}