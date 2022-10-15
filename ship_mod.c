//  C libs
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

//  Funkit libs
#include "system.h"


//  Game Libs
#include "setup.h"
#include "ship_mod.h"

Ship_t* ship_init(void)
{

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

    Ship_t* ships_to_return = ships;

    return ships_to_return;
}
