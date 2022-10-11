#include "system.h"
#include "pio.h"
#include "timer.h"
#include "navswitch.h"
#include <stdint.h>
#include <stdbool.h>
#include "display.h"

int main (void)
{
    display_init();

    display_pixel_set(0, 0, true);
    display_pixel_set(0, 6, true);
    display_pixel_set(4, 0, true);

    while (1) {
        display_update();
    }
}
