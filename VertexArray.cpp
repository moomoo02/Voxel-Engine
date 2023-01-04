#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

}

void VertexArray::bind() const
{
    glBindVertexArray(VAO);
}

//Creats a VBO for vertices and binds it to VAO based on vertex format.
void VertexArray::bindVBO(std::string key, VertexFormat vf, float vertices[], unsigned long verticesSizeBytes)
{
    //Create Vertex Buffer Object and bind to global state.
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSizeBytes, vertices, GL_STATIC_DRAW);

    //Store vbo as id
    VBOs[key] = VBO;

    //Bind Vertex BufferObject to VAO
    if(vf == VertexFormat_Texture){
        //For format: x, y, z, tx, ty
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0); 
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1); 
    }else if(vf == VertexFormat_RGB){
        //For format: x, y, z, r, g, b
        
    }

}