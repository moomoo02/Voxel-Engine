#ifndef __WATERTILE_H__
#define __WATERTILE_H__

class WaterTile {

    float height;
    float x,z;

public:
    static constexpr float TILE_SIZE = 10;

    WaterTile(float centerX, float centerZ, float height);

    float getHeight();
    float getX();
    float getZ();
};
#endif // __WATERTILE_H__