class WaterTile {

    float height;
    float x,z;

public:
    static constexpr float TILE_SIZE = 60;

    WaterTile(float centerX, float centerZ, float height);

    float getHeight();
    float getX();
    float getZ();
};