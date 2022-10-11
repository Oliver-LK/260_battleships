#include "system.h"
#include "setup.h"
#include "pio.h"
#include "navswitch.h"
#include <stdint.h>


uint8_t ship_setup() {

    bool setup_p = false;

    while (!setup_p) {
        pacer_wait();
        tinygl_update ();
        navswitch_update ();
        display_update();

        
    }
}