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


void ship_setup() {

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

    bool setupDone = false;
    bool takenSpacesMat[5][7] = {0};
    bool okayPlace = true;

    for (size_t i = 0; i < 4; i++) {
        setupDone = false;
        while (!setupDone) {
            pacer_wait();
            navswitch_update();
            button_update();
            okayPlace = true;

            /*Check for rotation*/
            if (navswitch_push_event_p(NAVSWITCH_PUSH)){

                /*Process to make sure the ship is within the matrix space*/
                if (ships[i].vertical) {
                    while (ships[i].xcoord + 3 > 4) {
                        ships[i].xcoord--;
                    }
                    ships[i].vertical = false;
                } else {
                    while (ships[i].ycoord + 3 > 6) {
                        ships[i].ycoord--;
                    }
                    ships[i].vertical = true;
                }
            }

            uint8_t offset = 0;

            /*Check for translation, and see whether the desired movement is within bounds*/
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                if (ships[i].ycoord > 0) {
                    ships[i].ycoord--;
                }
            }
            if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                if (ships[i].vertical) {
                    offset = ships[i].length - 1;
                }
                if (ships[i].ycoord < (6 - offset)) {
                    ships[i].ycoord++;
                }
            }
            if (navswitch_push_event_p (NAVSWITCH_EAST)) {
                if (!ships[i].vertical) {
                    offset = ships[i].length - 1;
                }
                if (ships[i].xcoord < (4 - offset)) {
                    ships[i].xcoord++;
                }
            }
            if (navswitch_push_event_p (NAVSWITCH_WEST)) {
                if (ships[i].xcoord > 0) {
                    ships[i].xcoord--;
                }
            }
            if (button_push_event_p(0)) {

                /*Check for overlaps*/
                if (ships[i].vertical) {
                    for (uint8_t j = 0; j < ships[i].length; j++) {
                        if (takenSpacesMat[ships[i].xcoord][ships[i].ycoord + j] == 1) {
                            okayPlace = false;
                        }
                    }
                } else {
                    for (uint8_t j = 0; j < ships[i].length; j++) {
                        if (takenSpacesMat[ships[i].xcoord + j][ships[i].ycoord] == 1) {
                            okayPlace = false;
                        }
                    }
                }
                if (okayPlace) {
                    for (uint8_t k = 0; k < ships[i].length; k++) {
                        if (ships[i].vertical) {
                            takenSpacesMat[ships[i].xcoord][ships[i].ycoord + k] = 1;
                        } else {
                            takenSpacesMat[ships[i].xcoord + k][ships[i].ycoord] = 1;
                        }
                    }
                    setupDone = true;
                }
            }

            /*Temporary display function for testing*/

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

            display_update();
        }
    }
}