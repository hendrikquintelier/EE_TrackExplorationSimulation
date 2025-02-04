#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../globals.h"
#include "MapPoint.h"
#include "FundamentalPath.h"

// Static counter for unique MapPoint IDs
static int map_point_counter = 0;

// Function to create a new Map Point
void initialize_map_point(MapPoint *mp, Location location, bool UltraSonicDetection[3]) {
    if (!mp) {
        perror("Null pointer passed to initialize_map_point");
        return;
    }

    // Assign unique ID and location
    mp->id = map_point_counter++;
    mp->location = location;

    // Count and initialize paths
    int trueCount = 0;
    for (int i = 0; i < 3; ++i) {
        if (UltraSonicDetection[i]) {
            trueCount++;
        }
    }

    mp->numberOfPaths = trueCount;

    for (int i = 0; i < trueCount; ++i) {
        initialize_fundamental_path(&mp->paths[i], mp, 0);
    }

    // Add to global array map_points_all
    if (num_map_points_all == capacity_map_points_all) {
        capacity_map_points_all *= 2;
        map_points_all = realloc(map_points_all, capacity_map_points_all * sizeof(MapPoint));
        if (!map_points_all) {
            perror("Failed to resize map_points_all array");
            exit(EXIT_FAILURE);
        }
    }
    map_points_all[num_map_points_all++] = *mp;

    if (mp_has_unexplored_paths(mp)) {
        add_map_point_tbd(mp);
    }
}

// Function to add a MapPoint to the "To Be Discovered" list
void add_map_point_tbd(MapPoint *mp) {
    if (num_map_points_tbd == capacity_map_points_tbd) {
        capacity_map_points_tbd *= 2;
        map_points_tbd = realloc(map_points_tbd, capacity_map_points_tbd * sizeof(MapPoint));
        if (!map_points_tbd) {
            perror("Failed to expand map_points_tbd");
            exit(EXIT_FAILURE);
        }
    }
    map_points_tbd[num_map_points_tbd++] = *mp;
}

// Check if a mappoint has paths with an unknown endpoint
int mp_has_unexplored_paths(MapPoint *mp) {
    for (int i = 0; i < mp->numberOfPaths; i++) {
        if (mp->paths[i].end == NULL) {
            return 1;  // Found an unexplored path
        }
    }
    return 0;
}

// Function that prints the info stored in the map point
void print_map_point(const MapPoint *mp) {
    printf("MapPoint ID: %d\n", mp->id);
    printf("Location: (%d, %d)\n", mp->location.x, mp->location.y);
    printf("Number of Paths: %d\n", mp->numberOfPaths);

    for (int i = 0; i < mp->numberOfPaths; ++i) {
        printf("  Path %d -> End MapPoint ID: %s\n", i + 1,
               mp->paths[i].end ? "Known" : "Unknown");
    }
}

// Function to check if a MapPoint with current_location already exists
int check_map_point_already_exists() {
    for (int i = 0; i < num_map_points_all; i++) {
        if (map_points_all[i].location.x == current_car.current_location.x &&
            map_points_all[i].location.y == current_car.current_location.y) {
            return 1;  // MapPoint already exists
            }
    }
    return 0;  // No MapPoint found at current_location
}
