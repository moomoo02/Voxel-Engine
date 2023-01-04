#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include <glad/glad.h>


class VertexArray 
{
public:
    unsigned int VAO; //Vertex array object
    VertexArray();
    void bind();
};


#endif // __VERTEXARRAY_H__