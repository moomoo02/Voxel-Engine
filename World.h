#ifndef __WORLD_H__
#define __WORLD_H__

#include <noise/noise.h>
#include "noiseutils.h"
#include <iostream>

class World {
    utils::NoiseMap heightMap;
public:
    World();
    utils::NoiseMap getHeightMap(double x1, double x2, double y1, double y2) const;
};
#endif // __WORLD_H__