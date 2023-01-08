#include "Chunk.h"

std::vector<float> cube = {
        -0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f, -0.5f, 
        0.5f,  0.5f, -0.5f, 
        0.5f,  0.5f, -0.5f,  
        -0.5f,  0.5f, -0.5f,  
        -0.5f, -0.5f, -0.5f,  

        -0.5f, -0.5f,  0.5f,  
        0.5f, -0.5f,  0.5f,  
        0.5f,  0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f,  

        -0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f, -0.5f,  
        -0.5f, -0.5f, -0.5f,  
        -0.5f, -0.5f, -0.5f,  
        -0.5f, -0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,  

        0.5f,  0.5f,  0.5f,  
        0.5f,  0.5f, -0.5f,  
        0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f,  0.5f,  
        0.5f,  0.5f,  0.5f,  

        -0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f,  0.5f,  
        0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f, -0.5f,  

        -0.5f,  0.5f, -0.5f,  
        0.5f,  0.5f, -0.5f,  
        0.5f,  0.5f,  0.5f,  
        0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f, -0.5f, 
};

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
    const float HALF_CHUNK_SIZE = CHUNK_SIZE / 2;

    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int y = 0; y < CHUNK_SIZE; y++){
            for(int z = 0; z < CHUNK_SIZE; z++){

                //Set Active (testing purposes)
                pBlocks[x][y][z].setActive();

                if(pBlocks[x][y][z].isActive()){
                    //Add vertex to VAO
                    glm::vec3 modelCoord = glm::vec3( (float)x, (float)y, (float)z) - HALF_CHUNK_SIZE;
                    modelCoord *= 1.0f/(HALF_CHUNK_SIZE);
                    if(x <=1 && y <= 1 && z <= 1) std::cout << modelCoord.x << ' ' << modelCoord.y << ' ' << modelCoord.z << '\n';
                    createCube(modelCoord);
                }
            }
        }
    }
}

//Takes in model Coordinates and returns one cube of size 1/HALF_CHUNK_SIZE
std::vector<float> Chunk::createCube(glm::vec3 modelCoord)
{
    std::vector<float> cubeVertices;
    const float CUBE_SIZE = 2.0f / (float)CHUNK_SIZE;

    float offsetX = modelCoord.x + 0.5f, offsetY = modelCoord.y + 0.5, offsetZ = modelCoord.z + 0.5;

    for(int i = 0; i < cube.size(); i+=3){
        float x = (cube[i] - offsetX) * CUBE_SIZE;
    }
    return cubeVertices;
}
