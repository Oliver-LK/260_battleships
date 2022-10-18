#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "ir_uart.h"
#include "system.h"
#include "pio.h"
#include "led.h"
#include "pacer.h"

void sendchar(char ourchar) {
    ir_uart_putc(ourchar);
}

char recievechar(void) {
    char recievedchar = 0;
    if (ir_uart_read_ready_p()) {
        recievedchar = ir_uart_getc();
    }
    return recievedchar;
}

bool player1_check(void) {
    bool isplayer1 = true;
    char rchar = 0;
    while (rchar != 2) {
        pacer_wait();
        rchar = recievechar();
        if (rchar == 1) {
            isplayer1 = false;
            sendchar(2);
        } else {
            sendchar(1);
        }
    }
    sendchar(2);
    return isplayer1;



    // bool player1 = false;
    // char recieved = 0;
    // bool waitingforopp = true;
    // if (ir_uart_read_ready_p()) {
    //     recieved = ir_uart_getc();
    //     if (recieved == '!') {
    //         ir_uart_putc('!');
    //     }
    // } else {
    //     player1 = true;
    //     while (waitingforopp) {
    //         pacer_wait();
    //         ir_uart_putc('!');
    //         if (ir_uart_read_ready_p()) {
    //             recieved = ir_uart_getc();
    //             if (recieved == '!') {
    //                 waitingforopp = false;
    //             }
    //         }
    //     }
    // }
    // led_set(LED1, 1);
    // while (1) {
    // }
}