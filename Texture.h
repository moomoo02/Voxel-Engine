#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "stb_image.h"

class Texture
{
private:
    unsigned int textureId;
    int width, height;
    int colorChannels;
public:
    Texture(const std::string & filePath);

};