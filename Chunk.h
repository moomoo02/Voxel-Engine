#ifndef __CHUNK_H__
#define __CHUNK_H__

#include "Block.h"
#include "Renderer.h"
#include "vector"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Chunk {
public:
    Chunk();
    ~Chunk();
    void Update(float dt);
    void Render(Renderer * pRenderer);

    //Creates a cube (vector of floats at a position based on its index in chunk.
    std::vector<float> createCube(glm::vec3 modelCoord);
    static const int CHUNK_SIZE = 16;
private: // The blocks data
    Block * * * pBlocks;
};

#endif // __CHUNK_H__