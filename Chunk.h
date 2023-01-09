#ifndef __CHUNK_H__
#define __CHUNK_H__

#include "Block.h"
#include "Renderer.h"
#include "vector"
#include "map"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Chunk {
public:
    Chunk();
    ~Chunk();
    void update(float dt);
    VertexArray render();

    //Set up landscapes
    void setupSphere();

    //Creates a cube (vector of floats at a position based on its index in chunk.
    void createCube(std::vector<float> &vertices, Block block, glm::vec3 modelCoord);
    static const int CHUNK_SIZE = 64;
private: // The blocks data
    Block * * * pBlocks;
};



#endif // __CHUNK_H__