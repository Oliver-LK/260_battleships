//  To delete all .o files
//  find . -type f -name '*.o' -delete
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
#include "led.h"
#include "ledmat.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

//  Game Libraries
#include "setup.h"
#include "ship_mod.h"
#include "led_testing.h"
#include "set_up.h"
#include "test_case.h"
#include "attack.h"

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
    ir_uart_init();
    tinygl_init (PACER_FREQ);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    led_set (LED1, 0);
    display_clear();
}


int main (void)
{
    /*LED test*/
    // led_set(LED1, 1);
    // while (1) {

    // }

    initialisation();
    greetings();

    //  Sets up ship array
    Ship_t ships_to_place[] = {battle_ship_init(), destroyer1_init(), destroyer2_init(), patrol_boat_init()};
    Ship_t* ships[TOTAL_SHIPS * sizeof(Ship_t)] = {&ships_to_place[0], &ships_to_place[1], &ships_to_place[2], &ships_to_place[3]};
    
    //  Sets up board: NEEDS TO BE OPTIMIZED
    uint8_t** board_info = board_maker();
    uint8_t** shot_board = shot_matrix();

    //  Starts the ship placement phase
    uint8_t ship_index = 0;
    bool do_place_phase = true;
    while(do_place_phase == true) {
        if(ship_index == TOTAL_SHIPS) {
            do_place_phase = false;

        }
        ship_placement_phase(ships[ship_index], &ship_index, board_info);
        for(uint64_t index_ship = 0; index_ship <= ship_index; index_ship++){
            display_ship(ships[index_ship]);
        }

    }

    // //  TEST CASE: testing to see if ships are all there: Can be deleted when not needed
    // for(uint64_t index_ship = 0; index_ship <= TOTAL_SHIPS; index_ship++){
    //     test_ship_positions(ships[index_ship], false); //  bypass mode ON
    // }


    /*Check to see if this board is first to initialise, then make it player 1*/
    // bool isplayer1;
    // isplayer1 = player1_check();
    // bool my_turn = isplayer1;

    while (1) {
        sendchar("a");
    }
    
    char ourchar = "a";
    char newchar = 'a';
    while (1) {
        tinygl_update();
        newchar = recievechar();
        if (newchar >= 33 && newchar <= 126) {
            ourchar = newchar;
        }
        char buffer[2];
        buffer[0] = ourchar;
        buffer[1] = '\0';
        tinygl_text (buffer);
    }
    

    // if (isplayer1) {
    //     led_set(LED1, 1);
    //     while (1) {

    //     }
    // }


}
//     bool do_attack_phase = true;
//     Shot_t new_shot = {.xcoord = 0, .ycoord = 0, .num = 0};
//     Shot_t* shot_ptr = &new_shot;
//     while(do_attack_phase == true) {
//         attack_phase(board_info, shot_board, shot_ptr,  my_turn);
//     }



//     /*Start of while loop for game*/
//     bool game_over = false;

//     /*Large while loop for whole game*/
//     while (!game_over) {
//         if (player1) {
            
//         }

//     }
// }
