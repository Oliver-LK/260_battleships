

#ifndef ATTACK_H
#define ATTACK_H

#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    uint8_t xcoord;
    uint8_t ycoord;
} Shot_t;

uint8_t** shot_matrix(void);

void display_current_shot(Shot_t* current_shot);
void shot_movement(Shot_t* current_shot);
bool test_shot(uint8_t** shot_board, Shot_t* current_shot);
void select_shot(uint8_t** shot_board, Shot_t* current_shot);
uint8_t take_shot(uint8_t** shot_board, Shot_t* current_shot);
void attack_phase(uint8_t** board_info, uint8_t** shot_board, Shot_t* current_shot, bool my_turn);



#endif