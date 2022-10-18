

#ifndef ATTACK_H
#define ATTACK_H

#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    uint8_t xcoord;
    uint8_t ycoord;
    uint32_t num;
} Shot_t;

uint8_t** shot_matrix(void);

void display_current_shot(Shot_t* current_shot);
void display_shot_board(uint8_t** shot_board);
void shot_movement(Shot_t* current_shot);
bool test_shot(uint8_t** shot_board, Shot_t* current_shot);
void select_shot(uint8_t** shot_board, Shot_t* current_shot);
uint8_t take_shot(uint8_t** shot_board, Shot_t* current_shot);
void attack_phase(uint8_t** board_info, uint8_t** shot_board, Shot_t* current_shot, bool my_turn);

void display_shots(uint8_t** shot_board);
void display_change(void);



#endif