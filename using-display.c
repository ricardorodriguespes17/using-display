#include <stdio.h>

#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "pico/stdlib.h"

// arquivo .pio
#include "using-display.pio.h"

// define o numero do pino para cada led
#define BLUE_LED_PIN 11
#define GREEN_LED_PIN 13
// pino de saída
#define BUTTON_PIN_A 5
#define BUTTON_PIN_B 6
#define OUT_PIN 7

// configurações da PIO
PIO pio = pio0;
bool ok;
uint16_t i;
double r = 0.0, b = 0.0, g = 0.0;
uint offset;
uint sm;

void define_all_components();

int main() {
  // coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
  ok = set_sys_clock_khz(128000, false);
  stdio_init_all();
  define_all_components();

  while (true);
}

// define os pinos e os tipos dos componentes utilizados
void define_all_components() {
  // inicializar o led azul - GPIO11
  gpio_init(BLUE_LED_PIN);
  gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);
  // inicializar o led verde - GPIO13
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

void config_pio() {
  // configurações da PIO
  uint offset = pio_add_program(pio, &using_display_program);
  uint sm = pio_claim_unused_sm(pio, true);
  using_display_program_init(pio, sm, offset, OUT_PIN);
}
