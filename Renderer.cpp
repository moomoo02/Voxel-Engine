#include "Renderer.h"


void Renderer::draw(const VertexArray& va, Shader& shader) const
{
    va.bind();
    shader.use();

    glDrawArrays(GL_TRIANGLES, 0, 36); //mode, starting index, count
}


