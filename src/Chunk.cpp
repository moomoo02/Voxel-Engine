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
    {BlockType::BlockType_Default, glm::vec3(0.04f,0.44f,0.15f)},
    {BlockType::BlockType_Grass, glm::vec3(0.04f,0.44f,0.15f)},
    {BlockType::BlockType_Sand, glm::vec3(0.761f,0.698f,0.502f)},
    {BlockType::BlockType_Stone, glm::vec3(0.5725f,0.5569,0.5216)},
    {BlockType::BlockType_Ice, glm::vec3(0.2549f,0.9608f,0.9647f)},
    {BlockType::BlockType_Snow, glm::vec3(1.0f,1.0f,1.0f)}
};

std::map<BlockType, int> BlockTypeToId = 
{
    {BlockType::BlockType_Sand, 0},
    {BlockType::BlockType_Grass, 1},
    {BlockType::BlockType_Stone, 2},
    {BlockType::BlockType_Snow, 3}
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
    setupHeightMap();
}

void Chunk::setupHeightMap(){

  //Setup height map
  myModule.SetFrequency(0.01f);
  heightMapBuilder.SetSourceModule (myModule);
  heightMapBuilder.SetDestNoiseMap (heightMap);
  heightMapBuilder.SetDestSize (CHUNK_SIZE, CHUNK_SIZE);

  //Set up the image renderer of the height map
  rendererImage.SetSourceNoiseMap (heightMap);
  rendererImage.SetDestImage (image);
  rendererImage.ClearGradient ();
  rendererImage.AddGradientPoint (-1.0000, utils ::Color (  0,   0, 128, 255)); // deeps
  rendererImage.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
  rendererImage.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
  rendererImage.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
  rendererImage.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
  rendererImage.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
  rendererImage.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
  rendererImage.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow
  writer.SetSourceImage (image);
  writer.SetDestFilename ("tutorial.bmp");
}

BlockType Chunk::getBlockTypeFromHeight(int height)
{
    if(height <= 3 * CHUNK_SIZE / 10){
      return BlockType_Sand;
    }else if(height <= 5* CHUNK_SIZE/10){
      return BlockType_Grass;
    }else if(height <= 9*CHUNK_SIZE/10){
      return BlockType_Stone;
    }
      
    return BlockType_Snow;
    
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

// std::vector<float> Chunk::render()
// {
//     //Initialize VAO
//     std::vector<float> vertices;
//     const float HALF_CHUNK_SIZE = CHUNK_SIZE / 2;

//     //glm::mat4 rotationMat(1);
//     //rotationMat = glm::rotate(rotationMat, (float)glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));

//     //Get Vertices 
//     int count = 0;
//     for(int x = 0; x < CHUNK_SIZE; x++){
//       for(int z = 0; z < CHUNK_SIZE; z++){
//         for(int y = 0; y < CHUNK_SIZE; y++){
//                 if(pBlocks[x][y][z].isActive()){
//                     //std::cout << "Active at ( " << x << " , " << y << " , " << z << " ) :" << '\n';
//                     if(isHiddenBlock(x,y,z)) continue;
//                     count++;
//                     //Add vertex to VAO
//                     glm::vec3 modelCoord = glm::vec3( (float)x, (float)y, (float)z) - HALF_CHUNK_SIZE; // from -Half to Half
//                     modelCoord *= 1.0f/(HALF_CHUNK_SIZE)/2.0f; //from -0.5 to 0.5
//                     //modelCoord = glm::vec3(rotationMat * glm::vec4(modelCoord, 1.0));
//                     createCube(vertices, pBlocks[x][y][z], modelCoord);
//                 }
//             }
//         }
//     }
    
//     // std::cout << count << " Rendered\n";
//     //Bind a Vertex Buffer Object
//     return vertices;
// }

std::vector<float> Chunk::render()
{
    //Initialize VAO
    std::vector<float> vertices;

    //glm::mat4 rotationMat(1);
    //rotationMat = glm::rotate(rotationMat, (float)glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));

    //Get Vertices 
    int count = 0;
    for(int x = 0; x < CHUNK_SIZE; x++){
      for(int z = 0; z < CHUNK_SIZE; z++){
        for(int y = 0; y < CHUNK_SIZE; y++){
                if(pBlocks[x][y][z].isActive()){
                    //std::cout << "Active at ( " << x << " , " << y << " , " << z << " ) :" << '\n';
                    if(isHiddenBlock(x,y,z)) continue;
                    count++;
                    //Add vertex to VAO
                    glm::vec3 modelCoord = glm::vec3(x, y, z); // from 0 to 31
                    //modelCoord = glm::vec3(rotationMat * glm::vec4(modelCoord, 1.0));
                    createCube(vertices, pBlocks[x][y][z], modelCoord);
                }
            }
        }
    }
    
    // std::cout << count << " Rendered\n";
    //Bind a Vertex Buffer Object
    return vertices;
}

void Chunk::createCube(std::vector<float> &vertices, Block block, glm::vec3 modelCoord)
{
    
    for(int i = 0; i < cube.size(); i+=6){
        int x = (cube[i] + 0.5 + modelCoord.x); // [-0.5, 0.5] + 0.5 = [0,1] -> [0,1] + [0,31] = [0,32]
        int y = (cube[i + 1] + 0.5 + modelCoord.y);
        int z = (cube[i + 2] + 0.5 + modelCoord.z);

        int nx = (cube[i+3] == -1.0 ? 2 : cube[i+3]);
        int ny = (cube[i+4] == -1.0 ? 2 : cube[i+4]);
        int nz = (cube[i+5] == -1.0 ? 2 : cube[i+5]);
        
        int position = x | y << 6 | z << 12; //18 bits
        int normal = nx | ny << 2 | nz << 4; //6 bits
        int color = BlockTypeToId[block.getBlockType()]; //2 bits

        int vertex = position | normal << 18 | color << 24; //  color (2 bits) + normal(6 bits) + position(18 bits) 

        vertices.push_back(vertex);
    }
}

//model coordinates represent bottom, left, back coord of cube (-x, -y, -z)
//Takes in model Coordinates and returns one cube of size 1/HALF_CHUNK_SIZE
// void Chunk::createCube(std::vector<float> &vertices, Block block, glm::vec3 modelCoord)
// {
    
//     float offsetX = -0.5f/CHUNK_SIZE - modelCoord.x, offsetY = -0.5f/CHUNK_SIZE - modelCoord.y, offsetZ = -0.5f/CHUNK_SIZE - modelCoord.z;
//     // std::cout << offsetXX << ' ' << offsetYY<< ' ' << offsetZZ << '\n';
//     for(int i = 0; i < cube.size(); i+=6){
//         float x = (cube[i]/CHUNK_SIZE - offsetX);
//         float y = (cube[i + 1]/CHUNK_SIZE - offsetY);
//         float z = (cube[i + 2]/CHUNK_SIZE - offsetZ);
//         glm::vec3 blockColor = BlockTypeToColorMap[block.getBlockType()];  
//         //std::cout << xx << ' ' << yy<< ' ' << zz << '\n';
//         vertices.push_back(x);
//         vertices.push_back(y);
//         vertices.push_back(z);
//         vertices.push_back(cube[i+3]);
//         vertices.push_back(cube[i+4]);
//         vertices.push_back(cube[i+5]);
//         vertices.push_back(blockColor.x);
//         vertices.push_back(blockColor.y);
//         vertices.push_back(blockColor.z);
//     }
// }

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

void Chunk::setupLandscape(double dx, double dy) {

  //Noise
  heightMapBuilder.SetBounds (dx, dx + CHUNK_SIZE - 1, dy, dy + CHUNK_SIZE - 1);
  heightMapBuilder.Build ();
  rendererImage.Render ();
  // std::string key = "tutorial" + std::to_string((int)dx) + std::to_string((int)dy) + ".bmp";
  // writer.SetDestFilename (key);
  // writer.WriteDestFile ();
  
  //Get heightmap
  //utils::NoiseMap heightMap = world->getHeightMap(dx, dx + CHUNK_SIZE - 1, dy, dy + CHUNK_SIZE - 1);
  //utils::NoiseMap heightMap = world->getHeightMap(dx, dx + CHUNK_SIZE - 1, dy, dy + CHUNK_SIZE - 1);

  for (int x = 0; x < CHUNK_SIZE; x++) {
    for (int z = 0; z < CHUNK_SIZE; z++) { 
      // Use the noise library to get the height value of x, z                      
      // Use the height map texture to get the height value of x, z  
      //float height = std::min((float)CHUNK_SIZE,(heightMap.GetValue(x + dx, z + dy) * (CHUNK_SIZE/2.0f) * 1.0f)); 
      float height = std::min((float)CHUNK_SIZE,((heightMap.GetValue(x,CHUNK_SIZE - 1 - z)+1.0f) * (CHUNK_SIZE/2.0f) * 1.0f));
      for (int y = 0; y < height; y++) {
        pBlocks[x][y][z].setActive(true);
        pBlocks[x][y][z].setBlockType(getBlockTypeFromHeight((int)y));
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
  int hiddenCount = 0;
  if(x > 0 && pBlocks[x-1][y][z].isActive()) hiddenCount++;
  if(x < CHUNK_SIZE - 1 && pBlocks[x+1][y][z].isActive()) hiddenCount++;

  if(y > 0 && pBlocks[x][y-1][z].isActive()) hiddenCount++;
  if(y < CHUNK_SIZE - 1 && pBlocks[x][y+1][z].isActive()) hiddenCount++;

  if(z > 0 && pBlocks[x][y][z-1].isActive()) hiddenCount++;
  if(z < CHUNK_SIZE - 1 && pBlocks[x][y][z+1].isActive()) hiddenCount++;

  return (hiddenCount == 6);
}
