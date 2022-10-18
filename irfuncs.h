#ifndef IRFUNCS_H
#define IRFUNCS_H
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "ir_uart.h"
#include "system.h"
#include "pio.h"
#include "led.h"

void sendchar(char ourchar);

char recievechar(void);

bool player1_check(void);

#endif