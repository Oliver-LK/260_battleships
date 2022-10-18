/*  File:   attack.c
    Author: Michael Rivers and Oliver Clements
    Date:   19 Oct 2022
    Descr:  This module contains all the functions related to the attack phase of the game.
            Includes selecting where you want to shoot and indicates if hit or miss. */

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
#include "irfuncs.h"

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

void display_change()
{
    display_update();
    display_clear();
}

void display_current_shot(Shot_t* current_shot)
{
    display_pixel_set(current_shot->xcoord, current_shot->ycoord, true);
}

void display_shots(uint8_t** shot_board)
{
    for(uint8_t y_row = 0; y_row < MAX_BOARD_HEIGHT; y_row++) {
        for(uint8_t x_row = 0; x_row < MAX_BOARD_WIDTH; x_row++) {
            shot_board[y_row][x_row] == 1 ? display_pixel_set(x_row, y_row, true) : NULL;
        }
    }
    display_change();

}

void wait(void)
{
    for(uint8_t index = 0; index < FLASH_RATE; index++) {
        pacer_wait();
    }
}

void indicate_hit(void) 
{
    led_set(LED1, 0);
    for(uint8_t number = 0; number < NUM_FLASHES; number++) {
        led_set(LED1, 1);
        wait();
        led_set(LED1, 0);
        wait();
    }
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

void select_shot(uint8_t** shot_board, Shot_t* current_shot, bool* my_turn)
{
    if((button_push_event_p(0)) && test_shot(shot_board, current_shot) == true) {
        shot_board[current_shot->ycoord][current_shot->xcoord] = 1;
        *my_turn = false; 
    }
}

void take_shot(uint8_t** shot_board, Shot_t* current_shot, bool* my_turn)
{
    shot_movement(current_shot);
    display_current_shot(current_shot);
    select_shot(shot_board, current_shot, my_turn);
}



void attack_phase(Ship_t* current_ship, uint8_t** shot_board, Shot_t* current_shot, bool* my_turn)
{
    if(*my_turn == true) {
        take_shot(shot_board, current_shot, my_turn);
        navswitch_update();
        button_update();
        display_shots(shot_board);
        if(*my_turn == false) {
            if(true) { // You hit the other player
                indicate_hit();
            }
            // send coords to player
            // led_set(LED1, 1);
        }

    } else if(*my_turn == false) {
        current_ship->hits[1] = 1; //  mimicking a hit on ur ship 
        display_ship(current_ship);
        display_change();

        //  have function that takes coords from other player
        //  have another function that tests these coords at board
        //  display board
    }

}
