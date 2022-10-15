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

//  Game Libraries
#include "setup.h"
#include "ship_mod.h"
#include "led_testing.h"

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

}

int main (void)
{
    initialisation();

    Ship_t* ships = ship_init();


    // ship_setup(ships);

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
