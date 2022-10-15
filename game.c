//  To delete all .o files
//  find . -type f -name '*.o' -delete
//  C Libraries
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

//  Fun kit Librariesj
#include "system.h"
#include "pio.h"
#include "timer.h"
#include "navswitch.h"
#include "display.h"
#include "pacer.h"
#include "button.h"
#include "led.h"
#include "ledmat.h"

//  Game Libraries
#include "setup.h"
#include "ship_mod.h"
#include "led_testing.h"

#define PACER_FREQ 500

/* Initialisation section*/
void lib_initialisation(void) 
{ 
    display_init();
    pacer_init(PACER_FREQ);
    system_init();
    navswitch_init();
    button_init();
    led_init();

    led_set (LED1, 0);
    display_clear();

}

void ship_init(void)
{
    Ship_t ships_to_place[] = {battle_ship_init(), destroyer1_init(), destroyer2_init(), patrol_boat_init()};
    Ship_t* ships[TOTAL_SHIPS * sizeof(Ship_t)] = {&ships_to_place[0], &ships_to_place[1], &ships_to_place[2], &ships_to_place[3]};

    for(uint8_t ship_index = 0; ship_index < TOTAL_SHIPS; ship_index++) {
        display_ship(ships[ship_index]);
    }
}

int main (void)
{
    lib_initialisation();
    ship_init();
    //  Ugly code but most passing the ship array around caused info to 'disappear'

    // for (size_t i = 0; i < 4; i++) {
    //     if (ships[i].vertical) {
    //         for (uint8_t j = 0; j < ships[i].length; j++) {
    //             display_pixel_set(ships[i].xcoord, ships[i].ycoord + j, true);
    //         }
    //     } else {
    //         for (uint8_t j = 0; j < ships[i].length; j++) {
    //             display_pixel_set(ships[i].xcoord + j, ships[i].ycoord, true);
    //         }
    //     }
    // }

    while (1) {
        display_update();
    }
}
