/*  File:   test_case.c
    Author: Michael Rivers and Oliver Clements
    Date:   19 Oct 2022
    Descr:  This module contains functions and test cases used in testing phase of code. */

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

void test_ship_positions(Ship_t* current_ship, bool test)
{
    while(test == true) {
        led_set (LED1, 1);
        for(uint64_t index_ship = 0; index_ship <= TOTAL_SHIPS; index_ship++){
            display_ship(current_ship);
            display_update();
        }
    }
}