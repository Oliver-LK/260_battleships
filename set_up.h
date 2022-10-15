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
void ship_placement_phase(Ship_t* current_ship, uint8_t* ship_index);
void translation(Ship_t* current_ship);
void rotation(Ship_t* current_ship);
void placement(uint8_t* ship_index);

#endif