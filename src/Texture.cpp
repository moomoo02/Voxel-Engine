#include "Texture.h"

Texture::Texture(const std::string & filePath, const unsigned int slot)
{
    std::cout << "Loading Texture: " << filePath << '\n';
    stbi_set_flip_vertically_on_load(true); 

    //Load Texture
    int w, h, nrChannels;
    unsigned char *data = stbi_load(filePath.c_str(), &w, &h, &nrChannels, 0);
    width = w;
    height = h;
    colorChannels = nrChannels;

    unsigned int texture;
    glGenTextures(1, &texture);  
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture);  
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_FLOAT, data);
    ID = texture;
    
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

}
