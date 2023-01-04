#ifndef __CHUNK_H__
#define __CHUNK_H__

#include "Block.h"
class Chunk {
public:
    Chunk();
    ~Chunk();
    void Update(float dt);
    //void Render(OpenGLRenderer * pRenderer);
    static const int CHUNK_SIZE = 16;
private: // The blocks data
    Block * * * pBlocks;
};

#endif // __CHUNK_H__