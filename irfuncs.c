#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "system.h"
#include "pio.h"
#include "led.h"
#include "pacer.h"
#include "attack.h"
#include "irfuncs.h"
#include "ir_uart.h"

void sendchar(char ourchar) {
    ir_uart_putc(ourchar);
}

void sendnum(uint8_t number) {
    ir_uart_putc(number);
}

int8_t recievenum(void) {
    int8_t recievednum = -1;
    if (ir_uart_read_ready_p()) {
        recievednum = ir_uart_getc();
    }
    return recievednum;
}

char recievechar(void) {
    char recievedchar = 200;
    if (ir_uart_read_ready_p()) {
        recievedchar = ir_uart_getc();
    }
    return recievedchar;
}

// void sendtillconfirm(uint8_t number) {
//     bool notDone = true;
//     int8_t recnum = -1;
//     while (notDone) {
//         pacer_wait();
//         sendnum(number);
//         recnum = recievenum();
//         if (recnum != -1) {
//             notDone = false;
//         }
//     }
// }

// uint8_t confirmsent() {
//     bool notDone = true;
//     int8_t recnum = -1;
//     while (notDone) {
//         pacer_wait();
//         recnum = recievenum();
//         if (recnum != -1) {
//             sendnum(1);
//             notDone = false;
//         }
//     }
//     return recnum;
// }

bool sendandconfirm(uint8_t number) {
    sendnum(number);
    bool confirmed = false;
    int8_t recnum = recievenum();
    if (recnum != -1) {
        confirmed = true;
    }
    return confirmed;
}

int8_t recieveandconfirm() {
    int8_t recnum = recievenum();
    if (recnum != -1) {
        sendnum(1);
    }
    return recnum;
}

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

// /*Sends a shot to the other board, then waits for the boards repsonse as to whether it was a hit*/
// uint8_t hit_ask(Shot_t* shot) {
//     if (shot->xcoord == 4) {
//         led_set(LED1, 1);
//         while (1) {

//         }
//     }

//     /*NOTE: shot->xcoord is indeed 4, found via testing, yet the hit_tell func reads 1 still. This is the main problem, everything else seems to work???*/
//     /*also note: a lot of magic numbers, will change later*/

//     uint8_t confirmnum = 200;
//     while (confirmnum == 200) {
//         pacer_wait();
//         uint8_t sentnum = shot->xcoord;
//         sendnum(sentnum);
//         confirmnum = recievenum();
//     }
//     // led_set(LED1, 1);
//     // while (1) {

//     // }


//     confirmnum = 200;
//     while (confirmnum == 200) {
//         pacer_wait();
//         sendnum(shot->ycoord);
//         confirmnum = recievenum();
//     }
//     // led_set(LED1, 1);
//     // while (1) {

//     // }

//     uint8_t shot_hit = 200;
//     while (shot_hit != 10 && shot_hit != 20) {
//         shot_hit = recievenum();
//     }
//     // led_set(LED1, 1);
//     // while (1) {

//     // }
//     // if (shot_hit == 20) {
//     //     led_set(LED1, 1);
//     //     while (1) {

//     //     }
//     // }
//     return shot_hit;
// }


// /*Recieves shot data from the other board, then tells if it is a hit, then relays back that info*/
// void hit_tell(uint8_t** board) {
//     bool xcoordfound = 0;
//     uint8_t xcoord = 200;

//     uint8_t repeat_counter = 0;

//     while (!xcoordfound) {
//         pacer_wait();
//         xcoord = recievenum();

//         /*testing (why is xcoord one???? It shouldnt be....)*/
//         if (xcoord == 4) {
//             led_set(LED1, 1);
//             while (1) {

//             }
//         }

//         if (xcoord < 5) {
//             xcoordfound = true;
//             while (repeat_counter < 5) {
//                 pacer_wait();
//                 sendnum(1);
//                 repeat_counter += 1;
//             }
//         }
//     }
//     // if (xcoord == 1) {
//     //     led_set(LED1, 1);
//     //     while (1) {

//     //     }
//     // }
//     // while (1) {

//     // }


//     repeat_counter = 0;
//     bool ycoordfound = false;
//     uint8_t ycoord = 200;
//     while (!ycoordfound) {
//         pacer_wait();
//         ycoord = recievenum();
//         if (ycoord < 7) {
//             ycoordfound = true;
//             while (repeat_counter < 10) {
//                 pacer_wait();
//                 sendnum(1);
//                 repeat_counter += 1;
//             }
//         }
//     }
//     // led_set(LED1, 1);
//     // while (1) {

//     // }

//     // if (ycoord == 1) {
//     //     led_set(LED1, 1);
//     //     while (1) {

//     //     }
//     // }
//     // while (1) {

//     // }


//     uint8_t hit = 10;
//     if (board[xcoord][ycoord] == 1) {
//         hit = 20;
//         // led_set(LED1, 1);
//         // while (1) {

//         // }
//     }

//     // led_set(LED1, 1);
//     // while (1) {

//     // }

//     repeat_counter = 0;
//     while (repeat_counter < 10) {
//         pacer_wait();
//         sendnum(hit);
//         repeat_counter += 1;
//     }
//     // led_set(LED1, 1);
//     // while (1) {

//     // }
// }