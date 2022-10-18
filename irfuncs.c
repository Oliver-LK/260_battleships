#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "ir_uart.h"
#include "system.h"
#include "pio.h"
#include "led.h"
#include "pacer.h"

bool player1_check(void) {
    bool player1 = false;
    char recieved = 0;
    bool waitingforopp = true;
    if (ir_uart_read_ready_p()) {
        recieved = ir_uart_getc();
        if (recieved == '!') {
            ir_uart_putc('!');
        }
    } else {
        player1 = true;
        while (waitingforopp) {
            pacer_wait();
            ir_uart_putc('!');
            if (ir_uart_read_ready_p()) {
                recieved = ir_uart_getc();
                if (recieved == '!') {
                    waitingforopp = false;
                }
            }
        }
    }
    // led_set(LED1, 1);
    // while (1) {
    // }
    return (player1);
}