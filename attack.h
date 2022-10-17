

#ifndef ATTACK_H
#define ATTACK_H

#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    uint8_t xcoord;
    uint8_t ycoord;
} Shot_t;

void display_current_shot(Shot_t* current_shot);
uint8_t take_shot(Shot_t* current_shot);
void attack_phase(uint8_t** board_info, Shot_t* current_shot, bool my_turn);



#endif