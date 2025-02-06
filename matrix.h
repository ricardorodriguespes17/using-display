#ifndef MATRIX
#define MATRIX

// numero de leds na matriz
#define NUM_PIXELS 25
// pino da matriz de leds
#define OUT_PIN 7

void config_pio_matrix();
void draw_number(int number);

#endif