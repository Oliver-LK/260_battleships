//  C libs
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

//  Funkit libs
#include "system.h"
#include "ledmat.h"
#include "display.h"
#include "pio.h"

//  Game Libs
#include "setup.h"
#include "ship_mod.h"


void display_ship(Ship_t* ship)
{
    for(uint8_t ship_index = 0; ship_index < ship->length; ship_index++) {
        if(ship->vertical == true) {
                display_pixel_set(ship->xcoord, ship->ycoord + ship_index, true);
        } else if(ship->vertical == false) {
            display_pixel_set(ship->xcoord + ship_index, ship->ycoord, true);
        }
    }
}


Ship_t battle_ship_init(void) {
    Ship_t battle_ship = {
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
    return battle_ship;
}
Ship_t destroyer1_init(void) {
    Ship_t destroyer1 = {
        .xcoord = 1,
        .ycoord = 1,
        .length = 3,
        .vertical = true,
        .hits = {
            .hit1 = false,
            .hit2 = false,
            .hit3 = false,
            .hit4 = false
        }
    };
    return destroyer1;
}

Ship_t destroyer2_init(void) {
    Ship_t destroyer2 = {
        .xcoord = 2,
        .ycoord = 2,
        .length = 3,
        .vertical = true,
        .hits = {
            .hit1 = false,
            .hit2 = false,
            .hit3 = false,
            .hit4 = false
        }
    };
    return destroyer2;
}

Ship_t patrol_boat_init(void) {
    Ship_t patrol_boat = {
        .xcoord = 3,
        .ycoord = 3,
        .length = 2,
        .vertical = true,
        .hits = {
            .hit1 = false,
            .hit2 = false,
            .hit3 = false,
            .hit4 = false
        }
    };
    return patrol_boat;
}
