#ifndef SET_UP_H
#define SET_UP_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "ship_mod.h"

#define PACER_FREQ 500
#define MESSAGE_RATE 25
#define MAX_BOARD_HEIGHT 7
#define MAX_BOARD_WIDTH 5

void greetings(void);
void ship_placement(Ship_t* current_ship);
void translation(Ship_t* current_ship);
void rotation(Ship_t* current_ship);

#endif