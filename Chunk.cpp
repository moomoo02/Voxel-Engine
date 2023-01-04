#include "Chunk.h"

Chunk::Chunk()
{
    pBlocks = new Block **[CHUNK_SIZE];
    for(int i = 0; i < CHUNK_SIZE; i++){
        pBlocks[i] = new Block *[CHUNK_SIZE];
        for(int j = 0; j < CHUNK_SIZE; j++){
            pBlocks[i][j] = new Block [CHUNK_SIZE];
        }
    }
}

Chunk::~Chunk()
{
    for(int i = 0; i < CHUNK_SIZE; i++){
        for(int j = 0; j < CHUNK_SIZE; j++){
            delete[] pBlocks[i][j];
        }
        delete[] pBlocks[i];
    }
    delete[] pBlocks;
}

void Chunk::Update(float dt)
{
    
}

void Chunk::Render(Renderer * pRenderer)
{
    //Initialize VAO
    VertexArray VAO;
    std::vector<float> vertices;

    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int y = 0; y < CHUNK_SIZE; y++){
            for(int z = 0; z < CHUNK_SIZE; z++){
                if(pBlocks[x][y][z].isActive()){
                    //Add vertex to VAO


                }
            }
        }
    }
}

std::vector<float> Chunk::createCube(int x, int y, int z)
{
    
}
