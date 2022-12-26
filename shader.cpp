#include "shader.h"

//Helper Functions
struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource parseShader(const std::string filePath){
    std::ifstream infile(filePath);
    
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ShaderType currentShader = ShaderType::NONE;
    std::stringstream ss[2];
    std::string line;
    while(std::getline(infile, line)){

        if(line.find("#Shader") == std::string::npos){
            ss[(int)currentShader] << line << '\n';
        }

        if(line.find("Vertex") != std::string::npos){
            currentShader = ShaderType::VERTEX;
        }else if(line.find("Fragment") != std::string::npos){
            currentShader = ShaderType::FRAGMENT;
        }
    }

    return { ss[0].str(), ss[1].str()};
}   

static unsigned int compileAndLinkShaders(ShaderProgramSource shaderSource){
    //Extract Shader Program Source
    const char * vertexShaderSource =  shaderSource.VertexSource.c_str();
    const char * fragmentShaderSource = shaderSource.FragmentSource.c_str();

    //Compile vertext shader object
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Compile fragment shader object
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //Check if shaders successfully compiled
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {   
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glGetProgramiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Link Shaders to ShaderProgram
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //Shaders will now be used, can delete
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);  

    return shaderProgram;
}

//Shader Implementation
Shader::Shader(const std::string filePath){
    //Parse file into source code strings
    ShaderProgramSource shaderSource = parseShader(filePath);

    //Compile and link shaders
    unsigned int shaderProgram = compileAndLinkShaders(shaderSource);
    ID = shaderProgram;
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    int uniformLocation = glGetUniformLocation(ID, name.c_str());
    if(uniformLocation == -1){
        std::cout << "ERROR::SHADER::SETBOOL::UNIFORM_LOCATION_FAILED" << std::endl;
    }

    //Update Uniform value
    glUseProgram(ID);
    glUniform1i(uniformLocation, (int)value);
}  

void Shader::setInt(const std::string &name, int value) const {
    int uniformLocation = glGetUniformLocation(ID, name.c_str());
    if(uniformLocation == -1){
        std::cout << "ERROR::SHADER::SETINT::UNIFORM_LOCATION_FAILED" << std::endl;
    }

    //Update Uniform value
    glUseProgram(ID);
    glUniform1i(uniformLocation, value);
}   
void Shader::setFloat(const std::string &name, float value) const {
    int uniformLocation = glGetUniformLocation(ID, name.c_str());
    if(uniformLocation == -1){
        std::cout << "ERROR::SHADER::SETFLOAT::UNIFORM_LOCATION_FAILED" << std::endl;
    }

    //Update Uniform value
    std::cout << name << " was changed to " << value << '\n';
    glUseProgram(ID);
    glUniform1f(uniformLocation, value);
}





