#ifndef IRFUNCS_H
#define IRFUNCS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "ir_uart.h"
#include "system.h"
#include "pio.h"
#include "led.h"
#include "attack.h"

void sendchar(char ourchar);

void sendnum(uint8_t number);

int8_t recievenum(void);

char recievechar(void);

bool player1_check(void);

uint8_t hit_ask(Shot_t* shot);

void hit_tell(uint8_t** board);

#endif