/*  This is the attack phase where each player will be able to attack the other player */

//  C Libraries
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

//  Fun kit Libraries
#include "system.h"
#include "pio.h"
#include "timer.h"
#include "navswitch.h"
#include "display.h"
#include "pacer.h"
#include "button.h"
#include "tinygl.h"
#include "led.h"
#include "../fonts/font5x7_1.h"

//  Game Libraries
#include "ship_mod.h"
#include "set_up.h"
#include "attack.h"

uint8_t** shot_matrix(void) 
{
    uint8_t* values = calloc(MAX_BOARD_HEIGHT * MAX_BOARD_WIDTH, sizeof(uint8_t));
    uint8_t** board = malloc(MAX_BOARD_HEIGHT * sizeof(uint8_t*));
    for(int i=0; i<MAX_BOARD_HEIGHT; i++)
    {
        board[i] = values + i * MAX_BOARD_WIDTH;
    }

    return board;
}

void display_current_shot(Shot_t* current_shot)
{
    display_pixel_set(current_shot->xcoord, current_shot->ycoord, true);
}

void shot_movement(Shot_t* current_shot)
{
    if(navswitch_push_event_p(NAVSWITCH_SOUTH) && current_shot->ycoord < MAX_BOARD_HEIGHT - 1) {
        current_shot->ycoord++;
    }

    if(navswitch_push_event_p(NAVSWITCH_NORTH) && current_shot->ycoord > 0) {
        current_shot->ycoord--;
    }

    if(navswitch_push_event_p(NAVSWITCH_EAST) && current_shot->xcoord < MAX_BOARD_WIDTH - 1) {
        current_shot->xcoord++;
    }

    if(navswitch_push_event_p(NAVSWITCH_WEST) && current_shot->xcoord > 0) {
        current_shot->xcoord--;
    }
}

bool test_shot(uint8_t** shot_board, Shot_t* current_shot)
{
    if(button_push_event_p(0) && shot_board[current_shot->ycoord][current_shot->xcoord] == 1) {
        return false;
    } else {
        return true;
    }
}

void select_shot(uint8_t** shot_board, Shot_t* current_shot)
{
    if((button_push_event_p(0)) && test_shot(shot_board, current_shot) == true) {
        shot_board[current_shot->ycoord][current_shot->xcoord] = 1;
    }
}

uint8_t take_shot(uint8_t** shot_board, Shot_t* current_shot)
{
    shot_movement(current_shot);
    display_current_shot(current_shot);
    display_update();
    display_clear();

    select_shot(shot_board, current_shot);

    return 0;
}

void attack_phase(uint8_t** my_board_info, uint8_t** shot_board, Shot_t* current_shot, bool my_turn)
{
    if(my_turn == true) {
        uint8_t shot_pos = take_shot(shot_board, current_shot);
        navswitch_update();
        button_update();
    }

    
}


