#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include <glad/glad.h>
#include <map>
#include <string>
#include <vector>

enum VertexFormat{
    VertexFormat_Texture, // x, y, z, tx, ty
    VertexFormat_RGB,  // x, y, z, r, g, b
};

class VertexArray 
{
public:
    unsigned int VAO; //Vertex array object
    std::map<std::string, unsigned int> VBOs; //maps key to a VBO 

    VertexArray();
    void bind() const;
    //Binds Vertices to VAO
    void createVBO(std::string key, std::vector<float> vertices);
    void bindVBO(std::string key, VertexFormat vf);
};


#endif // __VERTEXARRAY_H__