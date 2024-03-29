#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  
struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
public:
    // the program ID
    unsigned int ID;
    ShaderProgramSource shaderSource;

    // constructor reads and builds the shader
    Shader(const std::string filePath);
    // use/activate the shader
    void use();
    // Stop using Shader
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 matrix) const;
    void setVec3(const std::string &name, glm::vec3 vec3) const;
    void setVec4(const std::string &name, glm::vec4 vec4) const;
};
  
#endif