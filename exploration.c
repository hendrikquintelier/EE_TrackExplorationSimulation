#include "exploration.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "track_files_PRIVATE/track_detection.h"
#include "track_files_PRIVATE/track_navigation.h"
#include "algorithm_structs_PUBLIC/MapPoint.h"



// Check if the car is at a MapPoint
int is_map_point() {
    int options = 0;
    if (!ultrasonic_sensors[0]) options++; // Can move forward
    if (!ultrasonic_sensors[1]) options++; // Can move left
    if (!ultrasonic_sensors[2]) options++; // Can move right

    return (options > 1);  // More than one option = MapPoint
}

// Decide the next move based on ultrasonic sensors
void decide_next_move() {
    if (!ultrasonic_sensors[0]) {
        move_forward(&current_car);
        return;
    }

    // If forward is blocked, turn left or right
    if (!ultrasonic_sensors[1]) {
        rotate_left(&current_car);
        move_forward(&current_car);
    } else if (!ultrasonic_sensors[2]) {
        rotate_right(&current_car);
        move_forward(&current_car);
    } else {
        // No way forward, turn around
        rotate_right(&current_car);
        rotate_right(&current_car);
    }
}

// Main function to start automatic exploration
void start_exploration() {
    while (1) {
        print_grid(current_car);

        // Update sensor readings before each move
        update_ultrasonic_sensors();


        // Check if current position is a MapPoint
        if (is_map_point()) {
            // Allocate memory for new MapPoint
            MapPoint *new_map_point = malloc(sizeof(MapPoint));
            if (!new_map_point) {
                perror("Failed to allocate memory for MapPoint");
                exit(EXIT_FAILURE);
            }

            // Set location based on the car's current position
            Location location = {current_car.current_location.x, current_car.current_location.y};

            // Pass the ultrasonic detection array
            initialize_map_point(new_map_point, location, ultrasonic_sensors);
        }


        // Move or turn if necessary
        decide_next_move();

        // Stop when track is fully explored
        if (num_map_points_tbd == 0) {
            printf("Exploration complete!\n");
            break;
        }

        usleep(100000);  // Slow down movement for realism
    }
}
