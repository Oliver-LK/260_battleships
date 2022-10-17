/*  Module where we can host test cases and save them for future use and debugging
    None of this will be used in the final game */

#ifndef TESTS_H
#define TESTS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ship_mod.h"

void test_ship_positions(Ship_t* ships, bool test);

#endif