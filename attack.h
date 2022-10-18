/*  File:   attack.h
    Author: Michael Rivers and Oliver Clements
    Date:   19 Oct 2022
    Descr:  This module contains all the functions related to the attack phase of the game.
            Includes selecting where you want to shoot and indicates if hit or miss. */

#ifndef ATTACK_H
#define ATTACK_H

#include <stdint.h>
#include <stdlib.h>

#define NUM_FLASHES 10
#define FLASH_RATE 50

typedef struct
{
    uint8_t xcoord;
    uint8_t ycoord;
} Shot_t;

uint8_t** shot_matrix(void);

void display_change(void);
void wait(void);
void display_current_shot(Shot_t* current_shot);
void display_shots(uint8_t** shot_board);
void indicate_hit(void); 
void shot_movement(Shot_t* current_shot);
bool test_shot(uint8_t** shot_board, Shot_t* current_shot);
void select_shot(uint8_t** shot_board, Shot_t* current_shot, bool* my_turn);
void take_shot(uint8_t** shot_board, Shot_t* current_shot, bool* my_turn);
void attack_phase(Ship_t* current_ship, uint8_t** shot_board, Shot_t* current_shot, bool* my_turn);


#endif