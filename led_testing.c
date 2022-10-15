
//  C Libraries
#include <stdint.h>
#include <stdlib.h>

//  Fun kit Libraries
#include "system.h"
#include "led.h"
#include "pio.h"
#include "timer.h"

//  Game Libraries
#include "led_testing.h"

//  Flashes an LED
void flash_led(int8_t time)
{
    led_set (LED1, 1);
    timer_wait(1 * F_CPU);
    led_set (LED1, 0);

}