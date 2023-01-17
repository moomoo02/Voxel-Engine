#include "GuiTexture.h"s


GuiTexture::GuiTexture(Texture texture, glm::vec2 position, glm::vec2 scale)
{
    this->texture = texture;
    this->position = position;
    this->scale = scale;
}


Texture GuiTexture::getTexture()
{
    return texture;
}

glm::vec2 GuiTexture::getPosition()
{
    return position;
}

glm::vec2 GuiTexture::getScale()
{
    return scale;;
}
