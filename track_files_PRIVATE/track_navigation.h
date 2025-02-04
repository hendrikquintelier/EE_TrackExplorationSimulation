#ifndef TRACK_NAVIGATION_H
#define TRACK_NAVIGATION_H

#include "track_generation.h"

// Symbols for navigation
#define PLAYER 'P'
#define LOOK_UP '^'
#define LOOK_DOWN 'v'
#define LOOK_LEFT '<'
#define LOOK_RIGHT '>'

// Player struct
typedef struct {
    int x, y;  // Player position
    char direction;  // Current orientation ('^', 'v', '<', '>')
} Player;

// Function declarations
void print_grid();
void rotate_left();
void rotate_right();
void move_forward();

#endif // TRACK_NAVIGATION_H
