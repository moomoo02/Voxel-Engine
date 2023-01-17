#include "WaterTile.h"


WaterTile::WaterTile(float centerX, float height, float centerZ){
    this->x = centerX;
    this->z = centerZ;
    this->height = height;
}

float WaterTile::getHeight(){
    return height;
}

float WaterTile::getX()
{
    return x;   
}

float WaterTile::getZ()
{
    return z;
}