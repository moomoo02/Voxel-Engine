#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "stb_image.h"

class Texture
{
public:
    unsigned int ID;
    int width, height;
    int colorChannels;
    Texture(const std::string & filePath);

};