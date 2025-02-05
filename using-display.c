#include <stdio.h>

#include "pico/stdlib.h"

// define o numero do pino para cada led
#define BLUE_LED_PIN 11
#define GREEN_LED_PIN 13
// define o numero do pino para cada botao
#define BUTTON_PIN_A 5
#define BUTTON_PIN_B 6

void define_all_components();

int main() {
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
