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
#include "set_up.h"
#include "ship_mod.h"

void greetings(void)
{
    led_set (LED1, 0);
    tinygl_init (PACER_FREQ);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    tinygl_text("Welcome! Push a button to continue\0"); 

    bool loop = true;
    while (loop != false) {
        pacer_wait();
        navswitch_update();
        button_update();
        tinygl_update();
        if(navswitch_push_event_p(NAVSWITCH_PUSH) || button_push_event_p(0)){
            loop = false;
        }
        
    }
    
}

void translation(Ship_t* current_ship)
{
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        if (current_ship->ycoord > 0) {
                current_ship->ycoord--;
            }
        }
    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        if (current_ship->ycoord + current_ship->length < MAX_BOARD_HEIGHT && current_ship->vertical == true) {
            current_ship->ycoord++;

        } else if((current_ship->ycoord < MAX_BOARD_HEIGHT - 1) && current_ship->vertical == false) {
            current_ship->ycoord++;
        }
    }

    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        if (current_ship->xcoord < MAX_BOARD_WIDTH - 1 && current_ship->vertical == true) {
            current_ship->xcoord++;
        } else if(current_ship->xcoord + current_ship->length < MAX_BOARD_WIDTH && current_ship->vertical == false) {
            current_ship->xcoord++;
        }
        }
    if (navswitch_push_event_p (NAVSWITCH_WEST)) {
        if (current_ship->xcoord > 0) {
            current_ship->xcoord--;
            // offset = current_ship->length - 1;
        }
    }
}

void rotation(Ship_t* current_ship)
{
    //  Could make another function that deals with these rotation conditions to make more readable
    if (navswitch_push_event_p(NAVSWITCH_PUSH) && current_ship->vertical == true && current_ship->xcoord + current_ship->length < MAX_BOARD_WIDTH + 1){
        current_ship->vertical = false;
    } else if (navswitch_push_event_p(NAVSWITCH_PUSH) && current_ship->vertical == false && current_ship->ycoord + current_ship->length < MAX_BOARD_HEIGHT + 1) {
        current_ship->vertical = true;
    }
    
}

bool test_overlap(Ship_t* current_ship, uint8_t** board_info)
{
    if(button_push_event_p(0)) {
        for(uint8_t index = 0; index < current_ship->length; index++) {
            if(current_ship->vertical == true && board_info[current_ship->ycoord +index][current_ship->xcoord] == 1) {
                return false;
            } 
            else if(current_ship->vertical == false && board_info[current_ship->ycoord][current_ship->xcoord + index] == 1) {
                return false;
            }
        }
    }
    return true;
}


void placement(Ship_t* current_ship, uint8_t* ship_index, uint8_t** board_info)
{
    bool valid_placement = test_overlap(current_ship, board_info);
    if(valid_placement == true && button_push_event_p(0)) {
        for(uint8_t index = 0; index < current_ship->length; index++) {
            if(current_ship->vertical == true) {
                board_info[current_ship->ycoord +index][current_ship->xcoord] = 1;
            } 
            else if(current_ship->vertical == false) {
                board_info[current_ship->ycoord][current_ship->xcoord + index] = 1;
            }
            
        }
        *ship_index = *ship_index + 1;
    }
    
}



void ship_placement_phase(Ship_t* current_ship, uint8_t* ship_index, uint8_t** board_info)
{   
    translation(current_ship);
    rotation(current_ship);
    placement(current_ship, ship_index, board_info);
    

    navswitch_update();
    button_update();

    display_ship(current_ship);
    display_update();
    display_clear();

}
    
