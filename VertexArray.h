#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include <glad/glad.h>
#include <map>
#include <string>


class VertexArray 
{
public:
    unsigned int VAO; //Vertex array object
    std::map<std::string, unsigned int> VBOs; //maps key to a VBO 

    VertexArray();
    void bind() const;
    void bindVBO(std::string key, float vertices[], unsigned long verticesSizeBytes);
};


#endif // __VERTEXARRAY_H__