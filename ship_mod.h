#ifndef SHIP_MOD_H
#define SHIP_MOD_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define TOTAL_SHIPS 4


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

Ship_t battle_ship_init(void);
Ship_t destroyer1_init(void);
Ship_t destroyer2_init(void);
Ship_t patrol_boat_init(void);

void display_ship(Ship_t* ship);

#endif