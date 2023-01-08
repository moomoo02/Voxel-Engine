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

void Chunk::update(float dt)
{
    
}

void Chunk::render(Renderer * pRenderer)
{
    //Initialize VAO
    VertexArray VAO;
    std::vector<float> vertices;
    
    std::cout << "Render\n";
    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int y = 0; y < CHUNK_SIZE; y++){
            for(int z = 0; z < CHUNK_SIZE; z++){

                //Set Active (testing purposes)
                pBlocks[x][y][z].setActive();

                if(pBlocks[x][y][z].isActive()){
                    //Add vertex to VAO
                    glm::vec3 modelCoord = glm::vec3( (float)x, (float)y, (float)z) * 1.0f/(CHUNK_SIZE - 1.0f);
                    std::cout << x << ' ' << y << ' ' << z << " -> " << modelCoord.x << ' ' << modelCoord.y <<  ' ' << modelCoord.z << '\n';
                    createCube(modelCoord);
                }
            }
        }
    }
}

std::vector<float> Chunk::createCube(glm::vec3 modelCoord)
{
    std::vector<float> cubeVertices;
    return cubeVertices;
}
