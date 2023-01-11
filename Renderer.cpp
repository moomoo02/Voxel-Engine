#include "Renderer.h"


void Renderer::draw(const VertexArray& va, Shader& shader) const
{
    va.bind();
    shader.use();

    glDrawArrays(GL_TRIANGLES, 0, va.getVBOSize() / getSize(va.vf)); //mode, starting index, count
}

int Renderer::getSize(VertexFormat vf) const{
    int size = sizeof(float);

    if(vf == VertexFormat_Texture){
        size *= 5;
    }else if(vf == VertexFormat_RGB){
        size *= 6;
    }else if(vf == VertexFormat_Default){
        size *= 3;
    }
    
    return size;
}

