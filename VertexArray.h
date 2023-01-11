#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include <glad/glad.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>
enum VertexFormat{
    VertexFormat_Texture, // x, y, z, tx, ty
    VertexFormat_RGB,  // x, y, z, r, g, b
    VertexFormat_Default, // x, y, z
    VertexFormat_Normal, //x, y, z, n1, n2, n3
};

class VertexArray 
{
public:
    unsigned int VAO; //Vertex array object
    VertexFormat vf;
    std::map<std::string, unsigned int> VBOs; //maps key to a VBO id

    VertexArray();
    VertexArray(VertexFormat vf);
    void bind() const;

    //Gets size of current vbo 
    int getVBOSize() const;
    VertexFormat getCurrentVertexFormat() const;
    int getVertexSizeBytes() const;
    //Creates VBO Object
    void createVBO(std::string key, std::vector<float> vertices);

    //Binds Vertices to VAO
    void bindVBO(std::string key) const;
};


#endif // __VERTEXARRAY_H__