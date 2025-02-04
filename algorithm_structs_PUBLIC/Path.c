#include <stdio.h>
#include <stdlib.h>
#include "Path.h"

// Initialize a Path
void initialize_path(Path *path, MapPoint *start, MapPoint *end) {
    if (!path || !start || !end) {
        perror("Null pointer passed to initialize_path");
        return;
    }

    path->start = start;
    path->end = end;
    path->totalDistance = 0;  // Default total distance

    // Find a route between start and end (not implemented yet)
    path->route = NULL;  // Placeholder for actual path-finding algorithm

    printf("Initialized Path from MapPoint %d to MapPoint %d\n", start->id, end->id);
}

// Print a Path
void print_path(const Path *path) {
    if (!path || !path->start || !path->end) {
        printf("Invalid Path\n");
        return;
    }

    printf("Path from MapPoint %d to MapPoint %d\n", path->start->id, path->end->id);

    if (path->route) {
        printf("Route:\n");
        FundamentalPath *current = path->route;
        while (current) {
            printf("  Path ID: %d | Start: %d | End: %d | Distance: %d\n",
                   current->id,
                   current->start ? current->start->id : -1,
                   current->end ? current->end->id : -1,
                   current->distance);
            current = NULL; // Placeholder, assuming more logic will be implemented
        }
    } else {
        printf("No route defined.\n");
    }

    printf("Total Distance: %d\n", path->totalDistance);
}
