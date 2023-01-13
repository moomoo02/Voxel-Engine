#ifndef __WORLD_H__
#define __WORLD_H__

#include <noise/noise.h>
#include "noiseutils.h"

class World {
    utils::NoiseMap heightMap;
public:
    World();
    utils::NoiseMap getHeightMap() const;
};
#endif // __WORLD_H__