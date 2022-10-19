/*  File:   irfuncs.c
    Author: Michael Rivers and Oliver Clements
    Date:   19 Oct 2022
    Descr:  This module contains all the basic functions used for IR communications */

//  C Libraries
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

//  Fun kit Libraries
#include "system.h"
#include "pio.h"
#include "led.h"
#include "pacer.h"
#include "ir_uart.h"

//  Game Libraries
#include "attack.h"
#include "irfuncs.h"

/*Sends one character*/
void sendchar(char ourchar) {
    
    ir_uart_putc(ourchar);
}

/*Equivalent to above function, but takes a uint8_t number and is easier to read in main code*/
void sendnum(uint8_t number) {

    ir_uart_putc(number);
}

/*Checks for IR transmission, then returns the number if there is a transmission, -1 if not*/
int8_t recievenum(void) {

    int8_t recievednum = -1;

    if (ir_uart_read_ready_p()) 
    {
        recievednum = ir_uart_getc();
    }

    return recievednum;
}

/*Same as above but for characters*/
char recievechar(void) {

    char recievedchar = -1;

    if (ir_uart_read_ready_p()) {

        recievedchar = ir_uart_getc();
    }

    return recievedchar;
}

/*Makes the first player to arrive at the function player 1, then waits for the second player to arrive setting them to player 2*/
bool player1_check(void) {

    bool isplayer1 = false;
    char newchar = 0;
    uint8_t counter = 0;

    while (counter < 10 && newchar != 1) {

        pacer_wait();
        newchar = recievechar();
        counter += 1;
    }

    if (newchar == 1) {

        sendchar(1);

    } else {

        isplayer1 = true;

        while (newchar != 1) {

            pacer_wait();
            sendchar(1);
            newchar = recievechar();
        }
    }

    return isplayer1;
}