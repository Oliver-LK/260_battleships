#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "ir_uart.h"
#include "system.h"
#include "pio.h"
#include "led.h"

bool player1_check(void) {
    bool player1 = false;
    char recieved;
    if (ir_uart_read_ready_p()) {
        recieved = ir_uart_getc();
        ir_uart_putc('!');
    } else {
        bool player1 = true;
        bool waitingforopp = true;
        while (waitingforopp) {
            ir_uart_putc('!');
            if (ir_uart_read_ready_p()) {
                recieved = ir_uart_getc();
                waitingforopp = false;
            }
        }
    }
    return player1;
}