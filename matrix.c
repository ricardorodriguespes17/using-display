#include "matrix.h"

#include "hardware/clocks.h"
#include "hardware/pio.h"
// arquivo .pio
#include "using-display.pio.h"

// configurações da PIO
PIO pio = pio0;
bool ok;
uint16_t i;
double r = 0.0, b = 0.0, g = 0.0;
uint offset;
uint sm;

// vetor para criar imagem na matriz de led - 1
double matrix_draws[10][NUM_PIXELS] = {
    {
        // numero 0
        0.3, 0.3, 0.3, 0.3, 0.3,  //
        0.3, 0.0, 0.0, 0.0, 0.3,  //
        0.3, 0.0, 0.0, 0.0, 0.3,  //
        0.3, 0.0, 0.0, 0.0, 0.3,  //
        0.3, 0.3, 0.3, 0.3, 0.3   //
    },
    {
        // numero 1
        0.0, 0.0, 0.3, 0.0, 0.0,  //
        0.0, 0.0, 0.3, 0.3, 0.0,  //
        0.0, 0.0, 0.3, 0.0, 0.0,  //
        0.0, 0.0, 0.3, 0.0, 0.0,  //
        0.0, 0.0, 0.3, 0.0, 0.0   //
    },
    {
        // numero 2
        0.3, 0.3, 0.3, 0.3, 0.3,  //
        0.3, 0.0, 0.0, 0.0, 0.0,  //
        0.3, 0.3, 0.3, 0.3, 0.3,  //
        0.0, 0.0, 0.0, 0.0, 0.3,  //
        0.3, 0.3, 0.3, 0.3, 0.3   //
    },
    {
        // numero 3
        0.3, 0.3, 0.3, 0.3, 0.3,  //
        0.3, 0.0, 0.0, 0.0, 0.0,  //
        0.3, 0.3, 0.3, 0.3, 0.3,  //
        0.3, 0.0, 0.0, 0.0, 0.0,  //
        0.3, 0.3, 0.3, 0.3, 0.3   //
    },
    {
        // numero 4
        0.3, 0.0, 0.0, 0.0, 0.3,  //
        0.3, 0.0, 0.0, 0.0, 0.3,  //
        0.3, 0.3, 0.3, 0.3, 0.3,  //
        0.3, 0.0, 0.0, 0.0, 0.0,  //
        0.0, 0.0, 0.0, 0.0, 0.3   //
    },
    {
        // numero 5
        0.3, 0.3, 0.3, 0.3, 0.3,  //
        0.0, 0.0, 0.0, 0.0, 0.3,  //
        0.3, 0.3, 0.3, 0.3, 0.3,  //
        0.3, 0.0, 0.0, 0.0, 0.0,  //
        0.3, 0.3, 0.3, 0.3, 0.3   //
    },
    {
        // numero 6
        0.3, 0.3, 0.3, 0.3, 0.3,  //
        0.0, 0.0, 0.0, 0.0, 0.3,  //
        0.3, 0.3, 0.3, 0.3, 0.3,  //
        0.3, 0.0, 0.0, 0.0, 0.3,  //
        0.3, 0.3, 0.3, 0.3, 0.3   //
    },
    {
        // numero 7
        0.3, 0.3, 0.3, 0.3, 0.3,  //
        0.3, 0.0, 0.0, 0.0, 0.0,  //
        0.0, 0.0, 0.0, 0.0, 0.3,  //
        0.3, 0.0, 0.0, 0.0, 0.0,  //
        0.0, 0.0, 0.0, 0.0, 0.3   //
    },
    {
        // numero 8
        0.3, 0.3, 0.3, 0.3, 0.3,  //
        0.3, 0.0, 0.0, 0.0, 0.3,  //
        0.3, 0.3, 0.3, 0.3, 0.3,  //
        0.3, 0.0, 0.0, 0.0, 0.3,  //
        0.3, 0.3, 0.3, 0.3, 0.3   //
    },
    {
        // numero 9
        0.3, 0.3, 0.3, 0.3, 0.3,  //
        0.3, 0.0, 0.0, 0.0, 0.3,  //
        0.3, 0.3, 0.3, 0.3, 0.3,  //
        0.3, 0.0, 0.0, 0.0, 0.0,  //
        0.3, 0.3, 0.3, 0.3, 0.3   //
    },
};

void config_pio_matrix() {
  // coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
  ok = set_sys_clock_khz(128000, false);
  // configurações da PIO
  uint offset = pio_add_program(pio, &using_display_program);
  uint sm = pio_claim_unused_sm(pio, true);
  using_display_program_init(pio, sm, offset, OUT_PIN);
}

// rotina para definição da intensidade de cores do led
uint32_t matrix_rgb(double b, double r, double g) {
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

// rotina para acionar a matrix de leds - ws2812b
void draw_in_matrix(double* draw) {
  uint32_t led_value;
  for (int16_t i = 0; i < NUM_PIXELS; i++) {
    int index = 24 - i;
    double pixel = draw[index];
    led_value = matrix_rgb(0.0, draw[24 - i], 0.0);
    pio_sm_put_blocking(pio, sm, led_value);
  }
}

void draw_number(int number) { draw_in_matrix(matrix_draws[number]); }