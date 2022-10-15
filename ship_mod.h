#ifndef SHIP_MOD_H
#define SHIP_MOD_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct {
    bool hit1;
    bool hit2;
    bool hit3;
    bool hit4;
} Hits_t;

typedef struct {
    uint8_t length;
    uint8_t xcoord;
    uint8_t ycoord;
    bool vertical;
    Hits_t hits;
    
} Ship_t;

Ship_t* ship_init(void);

#endif