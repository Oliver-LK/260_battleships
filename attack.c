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

/*Defines a 2D array that encodes the positions of all shots taken*/
uint8_t** shot_matrix(void) 
{
    uint8_t* values = calloc(MAX_BOARD_HEIGHT * MAX_BOARD_WIDTH, sizeof(uint8_t));
    uint8_t** board = malloc(MAX_BOARD_HEIGHT * sizeof(uint8_t*));

    for (uint8_t i = 0; i < MAX_BOARD_HEIGHT; i++)
    {
        board[i] = values + i * MAX_BOARD_WIDTH;
    }

    return board;
}

/*Clears and updates display*/
void display_change()
{
    display_update();
    display_clear();
}

/*Displays the desired shot*/
void display_current_shot(Shot_t* current_shot)
{
    display_pixel_set(current_shot->xcoord, current_shot->ycoord, true);
}

/*Displays the 2D array of shots*/
void display_shots(uint8_t** shot_board)
{
    for (uint8_t y_row = 0; y_row < MAX_BOARD_HEIGHT; y_row++) {

        for (uint8_t x_row = 0; x_row < MAX_BOARD_WIDTH; x_row++) {

            shot_board[y_row][x_row] == 1 ? display_pixel_set(x_row, y_row, true) : NULL;
        }
    }

    display_change();
}

/*Waits for an extended period of time, used for testing*/
void wait(void)
{
    for (uint8_t index = 0; index < FLASH_RATE; index++) {

        pacer_wait();
    }
}

/*Flashes the LED to represent ahit. The final version of the code doesn't use this function, as the code surrounding it malfunctioned*/
void indicate_hit(void) 
{
    led_set(LED1, 0);

    for (uint8_t number = 0; number < NUM_FLASHES; number++) {

        led_set(LED1, 1);
        wait();
        led_set(LED1, 0);
        wait();
    }
}

/*Allows posistioning of the show using the NAV switch*/
void shot_movement(Shot_t* current_shot)
{
    if (navswitch_push_event_p(NAVSWITCH_SOUTH) && current_shot->ycoord < MAX_BOARD_HEIGHT - 1) {

        current_shot->ycoord++;
    }

    if (navswitch_push_event_p(NAVSWITCH_NORTH) && current_shot->ycoord > 0) {

        current_shot->ycoord--;
    }

    if (navswitch_push_event_p(NAVSWITCH_EAST) && current_shot->xcoord < MAX_BOARD_WIDTH - 1) {

        current_shot->xcoord++;
    }

    if (navswitch_push_event_p(NAVSWITCH_WEST) && current_shot->xcoord > 0) {

        current_shot->xcoord--;
    }

}

/*Tests to see if the current shot. Eg not ontop of another shot*/
bool test_shot(uint8_t** shot_board, Shot_t* current_shot)
{
    if (button_push_event_p(0) && shot_board[current_shot->ycoord][current_shot->xcoord]) {

        return false;

    } else {

        return true;
    }
}

/*If the shot is valid then it will place the shot and switch your turn*/
void select_shot(uint8_t** shot_board, Shot_t* current_shot, bool* my_turn)
{
    if ((button_push_event_p(0)) && test_shot(shot_board, current_shot)) {

        shot_board[current_shot->ycoord][current_shot->xcoord] = 1;
        *my_turn = false; 
    }
}

/*This directions the previous 3 shot related functions and gives parameters*/
void take_shot(uint8_t** shot_board, Shot_t* current_shot, bool* my_turn)
{
    shot_movement(current_shot);
    display_current_shot(current_shot);
    select_shot(shot_board, current_shot, my_turn);
}


/*This is the attack phase the directs all attack phase related functions*/
void attack_phase(uint8_t** shot_board, Shot_t* current_shot, bool* my_turn, uint8_t** ship_board)
{
    if (*my_turn == true) {

        take_shot(shot_board, current_shot, my_turn);
        navswitch_update();
        button_update();
        display_shots(shot_board);

        if(*my_turn == false) {

           sendnum(SEND);
        }

    } else if (*my_turn == false) {

        display_matrix(ship_board);
        display_change();
        int8_t turnover = -1;
        turnover = recievenum();

        if (turnover == SEND) {

            *my_turn = true;
        }
    }

}
