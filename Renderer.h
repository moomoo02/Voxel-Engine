#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "VertexArray.h"
#include "Shader.h"
class Renderer
{
public:
    void draw(const VertexArray& va, Shader& shader) const;
};
#endif // __RENDERER_H__