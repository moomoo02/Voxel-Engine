#ifndef __GUI_H__
#define __GUI_H__

#include "../Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GuiTexture {
    Texture texture;
    glm::vec2 position;
    glm::vec2 scale;

public:
    GuiTexture(Texture texture, glm::vec2 position, glm::vec2 scale);
    Texture getTexture();
    glm::vec2 getPosition();
    glm::vec2 getScale();
    
};


#endif // __GUI_H__