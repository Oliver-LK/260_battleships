#include "system.h"
#include "pio.h"
#include "timer.h"
#include "navswitch.h"
#include <stdint.h>
#include <stdbool.h>
#include "display.h"
#include "pacer.h"
#include "button.h"
#include <stdlib.h>
#include "setup.h"
#define PACER_FREQ 500

//test

int main (void)
{
    /* Initialisation section*/
    display_init();
    pacer_init(PACER_FREQ);
    system_init();
    navswitch_init();
    button_init();

    // uint16_t counter = 0;
    // display_pixel_set(0, 0, true);
    // while (counter < 10000) {
    //     pacer_wait();
    //     counter++;
    //     display_update();
    // }
    Ship_t length4ship = {
        .xcoord = 0,
        .ycoord = 0,
        .length = 4,
        .vertical = true,
        .hits = {
            .hit1 = false,
            .hit2 = false,
            .hit3 = false,
            .hit4 = false
        }
    };

    Ship_t length3ship1 = {
        .xcoord = 0,
        .ycoord = 0,
        .length = 3,
        .vertical = true,
        .hits = {
            .hit1 = false,
            .hit2 = false,
            .hit3 = false,
            .hit4 = false
        }
    };

    Ship_t length3ship2 = {
        .xcoord = 0,
        .ycoord = 0,
        .length = 3,
        .vertical = true,
        .hits = {
            .hit1 = false,
            .hit2 = false,
            .hit3 = false,
            .hit4 = false
        }
    };

    Ship_t length2ship = {
        .xcoord = 0,
        .ycoord = 0,
        .length = 2,
        .vertical = true,
        .hits = {
            .hit1 = false,
            .hit2 = false,
            .hit3 = false,
            .hit4 = false
        }
    };

    Ship_t ships[4];
    ships[0] = length4ship;
    ships[1] = length3ship1;
    ships[2] = length3ship2;
    ships[3] = length2ship;

    ship_setup(&ships);

    display_clear();
    for (size_t i = 0; i < 4; i++) {
        if (ships[i].vertical) {
            for (uint8_t j = 0; j < ships[i].length; j++) {
                display_pixel_set(ships[i].xcoord, ships[i].ycoord + j, true);
            }
        } else {
            for (uint8_t j = 0; j < ships[i].length; j++) {
                display_pixel_set(ships[i].xcoord + j, ships[i].ycoord, true);
            }
        }
    }
    while (1) {
        display_update();
    }
}
