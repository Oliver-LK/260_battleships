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
#include "../fonts/font5x7_1.h"

//  Game Libraries
#include "set_up.h"
#include "ship_mod.h"

void greetings(void)
{
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
        if (current_ship->vertical == true && (current_ship->ycoord + current_ship->length) < MAX_BOARD_HEIGHT) {
            current_ship->ycoord++;
            // offset = current_ship->length - 1;
        }
    }

    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        if (current_ship->xcoord < MAX_BOARD_WIDTH - 1) {
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
    if (navswitch_push_event_p(NAVSWITCH_PUSH) && current_ship->vertical == true){
        current_ship->vertical = false;
    } else if (navswitch_push_event_p(NAVSWITCH_PUSH) && current_ship->vertical == false) {
        current_ship->vertical = true;
    }
    
}

void ship_placement(Ship_t* current_ship)
{   
    bool re_position = true;
    
    while(re_position == true) {
        translation(current_ship);
        rotation(current_ship);

        navswitch_update();


        display_ship(current_ship);
        display_update();
        display_clear();

        

    //     if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
    //         if (current_ship->ycoord > 0) {
    //                 current_ship->ycoord--;
    //             }
    //         }
    //         if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
    //             if (current_ship->vertical) {
    //                 offset = ships[i].length - 1;
    //             }
    //             if (ships[i].ycoord < (6 - offset)) {
    //                 ships[i].ycoord++;
    //             }
    //         }
    //         if (navswitch_push_event_p (NAVSWITCH_EAST)) {
    //             if (!ships[i].vertical) {
    //                 offset = ships[i].length - 1;
    //             }
    //             if (ships[i].xcoord < (4 - offset)) {
    //                 ships[i].xcoord++;
    //             }
    //         }
    //         if (navswitch_push_event_p (NAVSWITCH_WEST)) {
    //             if (ships[i].xcoord > 0) {
    //                 ships[i].xcoord--;
    //             }
    //         }
    }
}
    
