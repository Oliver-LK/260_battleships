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

    ship_setup();
}
