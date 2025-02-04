#include "track_generation.h"


// Define the global grid (now stored in track_generation.c)
char grid[GRID_SIZE][GRID_SIZE];

// Function to initialize the grid
void initialize_grid() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = EMPTY; // Default to empty space
        }
    }
}

// Function to create a **proper closed-loop track** (1-block width)
void create_loop_track() {
    // Start/Finish Line
    grid[1][4] = START_FINISH;

    // Top Section (Track Moves Down)
    grid[2][4] = TRACK;
    grid[3][4] = TRACK;
    grid[4][4] = TRACK;

    // Right Path
    grid[5][3] = TRACK;
    grid[6][3] = TRACK;
    grid[7][3] = TRACK;

    // Split points
    grid[5][4] = TRACK;
    grid[7][4] = TRACK;

    // Left Path
    grid[5][5] = TRACK;
    grid[6][5] = TRACK;
    grid[7][5] = TRACK;

    // Completing the Loop (Back to Start)
    grid[8][4] = TRACK;
    grid[9][4] = TRACK;
    grid[9][5] = TRACK;
    grid[9][6] = TRACK;
    grid[9][7] = TRACK;
    grid[8][7] = TRACK;
    grid[7][7] = TRACK;
    grid[6][7] = TRACK;
    grid[5][7] = TRACK;
    grid[4][7] = TRACK;
    grid[3][7] = TRACK;
    grid[2][7] = TRACK;
    grid[1][7] = TRACK;
    grid[1][6] = TRACK;
    grid[1][5] = TRACK;
}
