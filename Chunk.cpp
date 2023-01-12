#include "Chunk.h"


std::vector<float> cube = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

std::map<BlockType, glm::vec3> BlockTypeToColorMap = 
{
    {BlockType::BlockType_Default, glm::vec3(0.26f, 0.74f, 0.32f)},
    {BlockType::BlockType_Grass, glm::vec3(0.04f,0.44f,0.15f)}
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

std::vector<float> Chunk::render()
{
    //Initialize VAO
    std::vector<float> vertices;
    const float HALF_CHUNK_SIZE = CHUNK_SIZE / 2;

    //Get Vertices 
    int count = 0;
    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int y = 0; y < CHUNK_SIZE; y++){
            for(int z = 0; z < CHUNK_SIZE; z++){

                if(pBlocks[x][y][z].isActive()){
                    if(isHiddenBlock(x,y,z)) continue;
                    count++;
                    //Add vertex to VAO
                    glm::vec3 modelCoord = glm::vec3( (float)x, (float)y, (float)z) - HALF_CHUNK_SIZE;
                    modelCoord *= 1.0f/(HALF_CHUNK_SIZE);
                    createCube(vertices, pBlocks[x][y][z], modelCoord);
                }
            }
        }
    }
    
    std::cout << count << " Rendered\n";
    //Bind a Vertex Buffer Object
    return vertices;
}

//Takes in model Coordinates and returns one cube of size 1/HALF_CHUNK_SIZE
void Chunk::createCube(std::vector<float> &vertices, Block block, glm::vec3 modelCoord)
{
    const float CUBE_SIZE = 2.0f / (float)CHUNK_SIZE;
    
    float offsetX = modelCoord.x + 0.5f, offsetY = modelCoord.y + 0.5, offsetZ = modelCoord.z + 0.5;
    
    for(int i = 0; i < cube.size(); i+=6){
        float x = (cube[i] - offsetX) * CUBE_SIZE;
        float y = (cube[i + 1] - offsetY) * CUBE_SIZE;
        float z = (cube[i + 2] - offsetZ) * CUBE_SIZE;
        glm::vec3 blockColor = BlockTypeToColorMap[block.getBlockType()];  
        
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
        vertices.push_back(cube[i+3]);
        vertices.push_back(cube[i+4]);
        vertices.push_back(cube[i+5]);
        vertices.push_back(blockColor.x);
        vertices.push_back(blockColor.y);
        vertices.push_back(blockColor.z);
    }
}

void Chunk::setupSphere() {
  for (int z = 0; z < CHUNK_SIZE; z++) {
    for (int y = 0; y < CHUNK_SIZE; y++) {
      for (int x = 0; x < CHUNK_SIZE; x++) {
        if (sqrt((float)(x - CHUNK_SIZE / 2) * (x - CHUNK_SIZE / 2) + (y - CHUNK_SIZE / 2) * (y - CHUNK_SIZE / 2) + (z - CHUNK_SIZE / 2) * (z - CHUNK_SIZE / 2)) <= CHUNK_SIZE / 2) {
            pBlocks[x][y][z].setActive(true);
            pBlocks[x][y][z].setBlockType(BlockType_Grass);
        }
      }
    }
  }
}

void Chunk::setupCube() {
  for (int z = 0; z < CHUNK_SIZE; z++) {
    for (int y = 0; y < CHUNK_SIZE; y++) {
      for (int x = 0; x < CHUNK_SIZE; x++) {
        pBlocks[x][y][z].setActive(true);
        pBlocks[x][y][z].setBlockType(BlockType_Grass);
      }
    }
  }
}

void Chunk::setupLandscape(double translation) {

  //Noise
  module::Perlin myModule;
  utils::NoiseMap heightMap;
  utils::NoiseMapBuilderPlane heightMapBuilder;
  //myModule.SetFrequency (8.0);
  heightMapBuilder.SetSourceModule (myModule);
  heightMapBuilder.SetDestNoiseMap (heightMap);
  heightMapBuilder.SetDestSize (256, 256);
  heightMapBuilder.SetBounds (translation, translation + CHUNK_SIZE - 1, translation, translation + CHUNK_SIZE - 1);
  heightMapBuilder.Build ();
  utils::RendererImage rendererImage;
  utils::Image image;
  rendererImage.SetSourceNoiseMap (heightMap);
  rendererImage.SetDestImage (image);
  rendererImage.Render ();
  utils::WriterBMP writer;
  writer.SetSourceImage (image);
  writer.SetDestFilename ("tutorial.bmp");
  writer.WriteDestFile ();

  for (int x = 0; x < CHUNK_SIZE; x++) {
    for (int z = 0; z < CHUNK_SIZE; z++) { 
      // Use the noise library to get the height value of x, z                      
      // Use the height map texture to get the height value of x, z  
      float height = std::min((float)CHUNK_SIZE,(heightMap.GetValue(x, z) + 0.2f) * (CHUNK_SIZE - 1) * 1.0f);
      std::cout << "Height: " << height << '\n';
      for (int y = 0; y < height; y++) {
        pBlocks[x][CHUNK_SIZE - 1 - y][z].setActive(true);
        pBlocks[x][CHUNK_SIZE - 1 - y][z].setBlockType(BlockType_Grass);
      }
    }
  }
}

void Chunk::clearBlocks()
{
  for (int z = 0; z < CHUNK_SIZE; z++) {
    for (int y = 0; y < CHUNK_SIZE; y++) {
      for (int x = 0; x < CHUNK_SIZE; x++) {
        pBlocks[x][y][z].setActive(false);
      }
    }
  }
}
bool Chunk::isHiddenBlock(int x, int y, int z) const
{
  bool isHidden = 1;
  if(x > 0 && !pBlocks[x-1][y][z].isActive()) isHidden = 0;
  if(x < CHUNK_SIZE - 1 && !pBlocks[x+1][y][z].isActive()) isHidden = 0;

  if(y > 0 && !pBlocks[x][y-1][z].isActive()) isHidden = 0;
  if(y < CHUNK_SIZE - 1 && !pBlocks[x][y+1][z].isActive()) isHidden = 0;

  if(z > 0 && !pBlocks[x][y][z-1].isActive()) isHidden = 0;
  if(z < CHUNK_SIZE - 1 && !pBlocks[x][y][z+1].isActive()) isHidden = 0;

  return isHidden;
}
