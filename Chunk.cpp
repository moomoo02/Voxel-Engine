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


std::map<BlockType, glm::vec3> BlockTypeToColorMap = 
{
    {BlockType::BlockType_Default, glm::vec3(0.26f, 0.74f, 0.32f)},
    {BlockType::BlockType_Grass, glm::vec3(0.26f, 0.74f, 0.32f)}
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
                    createCube(pBlocks[x][y][z], modelCoord);
                }
            }
        }
    }

}

//Takes in model Coordinates and returns one cube of size 1/HALF_CHUNK_SIZE
std::vector<float> Chunk::createCube(Block block, glm::vec3 modelCoord)
{
    std::vector<float> cubeVertices;
    const float CUBE_SIZE = 2.0f / (float)CHUNK_SIZE;
    
    float offsetX = modelCoord.x + 0.5f, offsetY = modelCoord.y + 0.5, offsetZ = modelCoord.z + 0.5;

    for(int i = 0; i < cube.size(); i+=3){
        float x = (cube[i] - offsetX) * CUBE_SIZE;
        float y = (cube[i + 1] - offsetY) * CUBE_SIZE;
        float z = (cube[i + 2] - offsetZ) * CUBE_SIZE;
        glm::vec3 blockColor = BlockTypeToColorMap[block.getBlockType()];

        cubeVertices.push_back(x);
        cubeVertices.push_back(y);
        cubeVertices.push_back(z);
        cubeVertices.push_back(blockColor.x);
        cubeVertices.push_back(blockColor.y);
        cubeVertices.push_back(blockColor.z);
    }

    return cubeVertices;
}
