#include <stdio.h>
#include "globals.h"
#include "exploration.h"
#include "track_files_PRIVATE//track_generation.h"

int main() {
    initialize_grid();  // Initialize grid from track_generation
    create_loop_track();  // Create the track layout

    printf("Starting Automatic Exploration...\n");
    start_exploration();

    return 0;
}
