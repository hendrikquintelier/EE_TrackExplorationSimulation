#include <stdio.h>
#include <stdlib.h>
#include "FundamentalPath.h"
#include "MapPoint.h"

// Static counter for unique FundamentalPath IDs
static int fundamental_path_counter = 0;

void initialize_fundamental_path(FundamentalPath *fp, MapPoint *start, float distance) {
    if (!fp) {
        perror("Null pointer passed to initialize_fundamental_path");
        return;
    }

    fp->id = fundamental_path_counter++;
    fp->start = start;
    fp->end = NULL;
    fp->distance = distance;
    fp->direction = 0;

    printf("Initialized FundamentalPath ID: %d\n", fp->id);
}

FundamentalPath* initialize_fundamental_paths(bool UltraSonicDetection[3]) {
    int trueCount = 0;
    for (int i = 0; i < 3; ++i) {
        if (UltraSonicDetection[i]) {
            trueCount++;
        }
    }

    FundamentalPath* paths = malloc(trueCount * sizeof(FundamentalPath));
    if (!paths) {
        perror("Failed to allocate memory for FundamentalPaths");
        exit(EXIT_FAILURE);
    }

    int pathIndex = 0;
    for (int i = 0; i < 3; ++i) {
        if (UltraSonicDetection[i]) {
            initialize_fundamental_path(&paths[pathIndex++], NULL, 0);
        }
    }

    return paths;
}
