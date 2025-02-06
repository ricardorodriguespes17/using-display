#include <stdio.h>

#include "hardware/pio.h"
#include "matrix.h"
#include "pico/stdlib.h"

// define o numero do pino para cada led
#define BLUE_LED_PIN 11
#define GREEN_LED_PIN 12
// pino dos botoes
#define BUTTON_PIN_A 5
#define BUTTON_PIN_B 6

// configuracoes das interrupcoes
static volatile uint32_t last_time = 0;
// estados dos leds
static volatile bool blue_led_on = false;
static volatile bool green_led_on = false;

// define os metodos a serem utilizados abaixo
void define_all_components();
void verify_leds_status();
void config_buttons();

int main() {
  stdio_init_all();
  define_all_components();
  config_buttons();
  config_pio_matrix();

  while (true) {
    verify_leds_status();
    sleep_ms(100);
  }
}

// define os pinos e os tipos dos componentes utilizados
void define_all_components() {
  // inicializar o led azul - GPIO11
  gpio_init(BLUE_LED_PIN);
  gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);
  // inicializar o led verde - GPIO12
  gpio_init(GREEN_LED_PIN);
  gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

  // inicializar o botão de interrupção - GPIO5
  gpio_init(BUTTON_PIN_A);
  gpio_set_dir(BUTTON_PIN_A, GPIO_IN);
  gpio_pull_up(BUTTON_PIN_A);

  // inicializar o botão de interrupção - GPIO6
  gpio_init(BUTTON_PIN_B);
  gpio_set_dir(BUTTON_PIN_B, GPIO_IN);
  gpio_pull_up(BUTTON_PIN_B);
}

void verify_leds_status() {
  gpio_put(BLUE_LED_PIN, blue_led_on);
  gpio_put(GREEN_LED_PIN, green_led_on);
}

// rotina da interrupção
static void gpio_irq_handler(uint gpio, uint32_t events) {
  uint32_t current_time = to_us_since_boot(get_absolute_time());

  if (current_time - last_time > 200000) {
    last_time = current_time;
    if (gpio == BUTTON_PIN_A) {
      green_led_on = !green_led_on;
      blue_led_on = false;
    } else if (gpio == BUTTON_PIN_B) {
      blue_led_on = !blue_led_on;
      green_led_on = false;
    }
  }
}

void config_buttons() {
  // interrupção da gpio habilitada
  gpio_set_irq_enabled_with_callback(BUTTON_PIN_A, GPIO_IRQ_EDGE_FALL, 1,
                                     &gpio_irq_handler);
  gpio_set_irq_enabled_with_callback(BUTTON_PIN_B, GPIO_IRQ_EDGE_FALL, 1,
                                     &gpio_irq_handler);
}