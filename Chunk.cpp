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

    for(int i = 0; i < CHUNK_SIZE; i++){
        for(int j = 0; j < CHUNK_SIZE; j++){
            for(int k = 0; k < CHUNK_SIZE; k++){
                if(pBlocks[i][j][k].isActive()){
                    //Add vertex to VAO
                    

                }
            }
        }
    }
}
