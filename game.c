/*  File:   game.c
    Author: Michael Rivers and Oliver Clements
    Date:   19 Oct 2022
    Descr:  Main game file. Includes initiations and game schedular */

//  To delete all .o files
//  find . -type f -name '*.o' -delete
//  find . -type f -name '*.out' -delete
//  find . -type f -name '*.hex' -delete
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
#include "ship_mod.h"
#include "led_testing.h"
#include "set_up.h"
#include "test_case.h"
#include "attack.h"
#include "irfuncs.h"


/*  Initialisation section*/
void initialisation(void) 
{ 
    display_init();
    pacer_init(PACER_FREQ);
    system_init();
    navswitch_init();
    timer_init();
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

/*  This the the schedular which schedules all events and also declares any variables that will
    are used throughout most sections of the program. This includes the position of the ships
    for example */
int main (void)
{
    initialisation();
    greetings();

    //  Sets up ship array
    Ship_t ships_to_place[] = {battle_ship_init(), destroyer1_init(), destroyer2_init(), patrol_boat_init()};
    Ship_t* ships[TOTAL_SHIPS * sizeof(Ship_t)] = {&ships_to_place[0], &ships_to_place[1], &ships_to_place[2], &ships_to_place[3]};
    
    //  Sets up board: NEEDS TO BE OPTIMIZED
    uint8_t** ship_board = ship_board_maker();
    uint8_t** shot_board = shot_matrix();

    //  Starts the ship placement phase
    uint8_t ship_index = 0;
    bool do_place_phase = true;
    while(do_place_phase == true) {
        if(ship_index == TOTAL_SHIPS) {
            do_place_phase = false;
        }
        ship_placement_phase(ships[ship_index], &ship_index, ship_board);
        for(uint64_t index_ship = 0; index_ship <= ship_index; index_ship++){
            display_ship(ships[index_ship]);
        }
    }

    /*Check to see if this board is first to initialise, then make it player 1*/
    bool isplayer1;
    isplayer1 = player1_check();

    /*Test for player1 function*/
    // if (isplayer1) {
    //     led_set(LED1, 1);
    //     while (1) {
    //     }
    // }

    
    //Starts Attack phase
    bool do_attack_phase = true;
    Shot_t new_shot = {.xcoord = 0, .ycoord = 0};
    Shot_t* shot_ptr = &new_shot;
    bool my_turn = isplayer1;
    while(do_attack_phase == true) {
        for(uint8_t ship_indexer = 0; ship_indexer < TOTAL_SHIPS; ship_indexer++) {
            attack_phase(ships[ship_indexer], shot_board, shot_ptr, &my_turn);
        }
        // if(my_turn == false) {
        //     pacer_wait();
        // }
        
        // my_turn = true;
    }
    

    // bool do_attack_phase = true;
    // bool my_turn = isplayer1; 
    // Shot_t new_shot = {.xcoord = 0, .ycoord = 0, .num = 0};
    // Shot_t* shot_ptr = &new_shot;
    // while (do_attack_phase) {
    //     attack_phase(board_info, shot_board, shot_ptr,  my_turn);
    // }


    /*testing for send and recieve num functions*/
    /*WORKING*/
    // uint8_t rnum = 0;
    // if (isplayer1) {
    //     while (1) {
    //         pacer_wait();
    //         sendnum(4);
    //     }
    // } else {
    //     while (rnum != 4) {
    //         pacer_wait();
    //         rnum = recievenum();
    //     }
    //     led_set(LED1, 1);
    //     while (1) {
    //     }
    // }



    /*testing for new hit_ask and hit_tell functions*/
    // Shot_t new_shot = {.xcoord = 4, .ycoord = 4};
    // Shot_t* newr_shot = &new_shot;
    // uint8_t shot_hit = 0;
    // if (isplayer1) {
    //     shot_hit = hit_ask(newr_shot);
    //     if (shot_hit == 20) {
    //         // led_set(LED1, 1);
    //         // while (1) {

    //         // }
    //     }
    // } else {
    //     hit_tell(ship_board);
    // }

}


   /*Large while loop for whole game*/
