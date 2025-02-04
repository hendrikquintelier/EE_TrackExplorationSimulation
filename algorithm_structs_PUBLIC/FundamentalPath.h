#ifndef FUNDAMENTALPATH_H
#define FUNDAMENTALPATH_H
#include <stdbool.h>

struct MapPoint;

typedef struct FundamentalPath {
    int id;
    struct MapPoint *start;
    struct MapPoint *end;
    int distance;
    int direction;
} FundamentalPath;

void initialize_fundamental_path(FundamentalPath *fp, struct MapPoint *start, float distance);
FundamentalPath* initialize_fundamental_paths(bool UltraSonicDetection[3]);

#endif // FUNDAMENTALPATH_H
