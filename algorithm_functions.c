//
// Created by Hendrik Quintelier on 04/02/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "algorithm_structs_PUBLIC/MapPoint.h"
#include "algorithm_structs_PUBLIC/FundamentalPath.h"
#include "algorithm_structs_PUBLIC/Path.h"





// Check if a path has an unknown endpoint
int mp_has_unexplored_paths(MapPoint *mp) {
    for (int i = 0; i < mp->numberOfPaths; i++) {
        if (mp->paths[i].end == NULL) {
            return 1;  // Found an unexplored path
        }
    }
    return 0;
}

// Function to move forward if possible
FundamentalPath* move_forward(MapPoint *current) {
    for (int i = 0; i < current->numberOfPaths; i++) {
        if (current->paths[i].end != NULL) {
            return &current->paths[i]; // Continue moving forward
        }
    }
    return NULL; // No forward movement possible
}

// Function to find the next path to explore
FundamentalPath* find_next_path(MapPoint *current) {
    for (int i = 0; i < current->numberOfPaths; i++) {
        if (current->paths[i].end == NULL) {
            return &current->paths[i];  // Choose the first unexplored path
        }
    }
    return NULL;  // No unexplored paths available
}

// AI Navigation Algorithm
void explore_track(MapPoint *start) {
    MapPoint *current = start;

    while (1) {
        // If we reach a MapPoint with multiple paths, check for unexplored paths
        if (current->numberOfPaths > 1) {
            if (has_unexplored_paths(current)) {
                add_map_point_tbd(current);
            }
        }

        // Try to move forward if possible
        FundamentalPath *nextPath = move_forward(current);
        if (nextPath != NULL) {
            current = nextPath->end;  // Move to next MapPoint
        } else {
            // If we can't move forward, find an unexplored path
            nextPath = find_next_path(current);
            if (nextPath != NULL) {
                // Create a new MapPoint as the destination
                MapPoint *newPoint = malloc(sizeof(MapPoint));
                newPoint->id = num_map_points_all;
                newPoint->numberOfPaths = 0;
                newPoint->location = (Location){0, 0};  // Placeholder location

                // Link the new point
                nextPath->end = newPoint;
                add_map_point(newPoint);
                current = newPoint;
            } else {
                // No more paths to explore, stop
                break;
            }
        }
    }
}

