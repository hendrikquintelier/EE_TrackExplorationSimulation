#ifndef MAPPOINT_H
#define MAPPOINT_H

#include "FundamentalPath.h"
#include <stdbool.h>

typedef struct Location {
    int x;
    int y;
} Location;

typedef struct MapPoint {
    int id;
    FundamentalPath paths[4];
    int numberOfPaths;
    Location location;
} MapPoint;

// Function to create a new Map Point
void initialize_map_point(MapPoint *mp, Location location, bool UltraSonicDetection[3]);

// Function that prints the info stored in the map point
void print_map_point(const MapPoint *mp);

// Function to add a MapPoint to the "To Be Discovered" list
void add_map_point_tbd(MapPoint *mp);

// Check if a mappoint has paths with an unknown endpoint
int mp_has_unexplored_paths(MapPoint *mp);

// Function to check if a MapPoint with current_location already exists
int check_map_point_already_exists();

#endif // MAPPOINT_H
