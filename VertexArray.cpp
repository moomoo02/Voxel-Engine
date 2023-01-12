#include "VertexArray.h"


VertexArray::VertexArray()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    vf = VertexFormat_Default;
}

VertexArray::VertexArray(VertexFormat vertexformat)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    vf = vertexformat;

}

void VertexArray::bind() const
{
    glBindVertexArray(VAO);
}

int VertexArray::getVBOSize() const
{
    int size;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

    return size;
}


//Creates a vertex buffer object for vertices
void VertexArray::createVBO(std::string key, std::vector<float> vertices){
    //Create Vertex Buffer Object and bind to global state.
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    //Store vbo as id
    VBOs[key] = VBO;

}

void VertexArray::editVBO(std::string key, std::vector<float> vertices)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[key]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
}   

//Binds the current VBO of key to VAO.
void VertexArray::bindVBO(std::string key) const{
    glBindBuffer(GL_ARRAY_BUFFER, VBOs.at(key));

    //Bind Vertex BufferObject to VAO
    if(vf == VertexFormat_Texture){
        //For format: x, y, z, tx, ty
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0); 
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1); 
    }else if(vf == VertexFormat_RGB){
        //For format: x, y, z, r, g, b
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
    }else if(vf == VertexFormat_Default){
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
    }else if(vf == VertexFormat_Normal){
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
    }else if(vf == VertexFormat_Normal_RGB){
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
    }
}

int VertexArray::getVertexSizeBytes() const {
    int size = sizeof(float);

    if(vf == VertexFormat_Texture){
        size *= 5;
    }else if(vf == VertexFormat_RGB){
        size *= 6;
    }else if(vf == VertexFormat_Default){
        size *= 3;
    }else if(vf == VertexFormat_Normal){
        size *= 6;
    }else if(vf == VertexFormat_Normal_RGB){
        size *= 9;
    }
    
    return size;
}