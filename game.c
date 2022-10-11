#include "system.h"
#include "pio.h"
#include "timer.h"
#include "navswitch.h"
#include <stdint.h>
#include <stdbool.h>
#include "display.h"
#include "pacer.h"

#define PACER_FREQ 500

int main (void)
{
    /* Initialisation section*/
    display_init();
    pacer_init(PACER_FREQ);
    system_init();
    navswitch_init();
    tinygl_init(PACER_FREQ);

    ship_setup();
}
