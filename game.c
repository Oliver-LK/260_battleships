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

    //  Sets up board array
    uint8_t zero_row[] = {0, 0, 0, 0, 0};
    uint8_t* board_info[] = {zero_row, zero_row, zero_row, zero_row, zero_row, zero_row, zero_row};

    uint8_t ship_index = 0;
    bool loop = true;
    while(loop == true) {
        ship_placement_phase(ships[ship_index], &ship_index, board_info);
        for(uint64_t index_ship = 0; index_ship <= ship_index; index_ship++){
            display_ship(ships[index_ship]);
        }

    }
}
