#include "World.h"

World::World()
{
    //Noise
  module::Perlin myModule;
  utils::NoiseMap heightMap;
  utils::NoiseMapBuilderPlane heightMapBuilder;
  //myModule.SetFrequency (8.0);
  heightMapBuilder.SetSourceModule (myModule);
  heightMapBuilder.SetDestNoiseMap (heightMap);
  heightMapBuilder.SetDestSize (256, 256);
  heightMapBuilder.Build ();
  utils::RendererImage rendererImage;
  utils::Image image;
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
  rendererImage.Render ();
  utils::WriterBMP writer;
  writer.SetSourceImage (image);
  writer.SetDestFilename ("World.bmp");
  writer.WriteDestFile ();
}

utils::NoiseMap World::getHeightMap() const
{
    return heightMap;
}
