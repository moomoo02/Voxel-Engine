#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include <glad/glad.h>
#include <vector>

class VertexArray 
{
public:
    unsigned int VAO; //Vertex array object
    std::vector<unsigned int> VBOs;
    VertexArray();
    void bind();
    void bindVBO(float vertices[], unsigned long verticesSizeBytes);
};


#endif // __VERTEXARRAY_H__