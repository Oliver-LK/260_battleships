#ifndef SETUP_H
#define SETUP_H

#include <stdint.h>


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
    // uint8_t hits[length];
} Ship_t;

// typedef struct {
//     uint8_t xstart;
//     uint8_t xend;
//     uint8_t ystart;
//     uint8_t yend;
//     uint8_t length;
//     bool vertical;
//     Hits_t hits;
// } Ship_t;


// typedef struct {
//     uint8_t pos1x;
//     uint8_t pos1y;
//     uint8_t pos2x;
//     uint8_t pos2y;
//     uint8_t pos3x;
//     uint8_t pos3y;
//     uint8_t pos4x;
//     uint8_t pos4y;
// } Ships_t;

void ship_setup(Ship_t[4]);







#endif