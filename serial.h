#ifndef SERIAL
#define SERIAL

#include "inc/ssd1306.h"

extern ssd1306_t ssd;

void config_serial();
void print_serial(char *text);

#endif