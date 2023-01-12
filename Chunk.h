#ifndef __CHUNK_H__
#define __CHUNK_H__

#include "Block.h"
#include "Renderer.h"
#include "vector"
#include "map"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <random>

#include <noise/noise.h>
#include "noiseutils.h"

class Chunk {
private:
    bool isHiddenBlock(int x, int y, int z) const;
public:
    Chunk();
    ~Chunk();
    void update(float dt);
    std::vector<float> render();

    //Set up landscapes
    void setupSphere();
    void setupCube();
    void setupLandscape(double dx = 0, double dy = 0);

    //Reset blocks
    void clearBlocks();

    //Creates a cube (vector of floats at a position based on its index in chunk.
    void createCube(std::vector<float> &vertices, Block block, glm::vec3 modelCoord);
    static const int CHUNK_SIZE = 16;
private: // The blocks data
    Block * * * pBlocks;
};


#endif // __CHUNK_H__