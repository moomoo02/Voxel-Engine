#include "World.h"

World::World()
{
  //Noise
  module::Perlin myModule;
  utils::NoiseMap hm;
  utils::NoiseMapBuilderPlane heightMapBuilder;
  //myModule.SetFrequency (8.0);
  heightMapBuilder.SetSourceModule (myModule);
  heightMapBuilder.SetDestNoiseMap (hm);
  heightMapBuilder.SetDestSize (256, 256);
  heightMapBuilder.SetBounds (0,10,0,10);
  heightMapBuilder.Build ();
  heightMap = hm;
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
  std::cout << "World generated\n";
}

utils::NoiseMap World::getHeightMap(double x1, double x2, double y1, double y2) const
{
    utils::NoiseMapBuilderPlane heightMapBuilder;
    heightMapBuilder.SetBounds (x1, x2, y1, y2);
    heightMapBuilder.Build ();
  //   module::Perlin myModule;
  //   utils::NoiseMap heightMap;
  //   utils::NoiseMapBuilderPlane heightMapBuilder;
  //   //myModule.SetFrequency (8.0);
  //   heightMapBuilder.SetSourceModule (myModule);
  //   heightMapBuilder.SetDestNoiseMap (heightMap);
  //   heightMapBuilder.SetDestSize (256, 256);
  //   heightMapBuilder.SetBounds (x1, x2, y1, y2);
  //   heightMapBuilder.Build ();
  //     utils::RendererImage rendererImage;
  // utils::Image image;
  // rendererImage.SetSourceNoiseMap (heightMap);
  // rendererImage.SetDestImage (image);
  // rendererImage.ClearGradient ();
  // rendererImage.AddGradientPoint (-1.0000, utils ::Color (  0,   0, 128, 255)); // deeps
  // rendererImage.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
  // rendererImage.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
  // rendererImage.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
  // rendererImage.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
  // rendererImage.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
  // rendererImage.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
  // rendererImage.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow
  // rendererImage.Render ();
  // utils::WriterBMP writer;
  // writer.SetSourceImage (image);
  // writer.SetDestFilename ("World.bmp");
  // writer.WriteDestFile ();
    return heightMap;
}
