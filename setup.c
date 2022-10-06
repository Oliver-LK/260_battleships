#include "system.h"
#include "setup.h"
#include "pio.h"
#include "navswitch.h"
#include <stdint.h>


uint8_t ship_setup() {

    pacer_init(100);

    while (1) {

        pacer_wait();

        // put in display function here

        
    }
}