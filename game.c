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
#include "set_up.h"

#define PACER_FREQ 500

/* Initialisation section*/
void initialisation(void) 
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

int main (void)
{
    initialisation();
    greetings();

    //  Sets up ship array
    Ship_t ships_to_place[] = {battle_ship_init(), destroyer1_init(), destroyer2_init(), patrol_boat_init()};
    Ship_t* ships[TOTAL_SHIPS * sizeof(Ship_t)] = {&ships_to_place[0], &ships_to_place[1], &ships_to_place[2], &ships_to_place[3]};
    
    //  Sets up board
    uint8_t zero_row1[] = {0, 0, 0, 0, 0};
    uint8_t zero_row2[] = {0, 0, 0, 0, 0};
    uint8_t zero_row3[] = {0, 0, 0, 0, 0};
    uint8_t zero_row4[] = {0, 0, 0, 0, 0};
    uint8_t zero_row5[] = {0, 0, 0, 0, 0};
    uint8_t zero_row6[] = {0, 0, 0, 0, 0};
    uint8_t zero_row7[] = {0, 0, 0, 0, 0};
    uint8_t* board_info[] = {zero_row1, zero_row2, zero_row3, zero_row4, zero_row5, zero_row6, zero_row7};

    uint8_t ship_index = 0;
    bool place_phase = true;
    while(place_phase == true) {
        if(ship_index == TOTAL_SHIPS) {
            place_phase = false;

        }
        ship_placement_phase(ships[ship_index], &ship_index, board_info);
        for(uint64_t index_ship = 0; index_ship <= ship_index; index_ship++){
            display_ship(ships[index_ship]);
        }

    }

    //  testing to see if ships are all there
    while(1) {
        led_set (LED1, 1);
        for(uint64_t index_ship = 0; index_ship <= TOTAL_SHIPS; index_ship++){
            display_ship(ships[index_ship]);
            display_update();
        }
    }
}
