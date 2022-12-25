#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

struct vec4{
    float x;
    float y;
    float z;
    float w;

    vec4(float firstValue, float secondValue, float thirdValue, float fourthValue){
        x = firstValue;
        y = secondValue;
        z = thirdValue;
        w = fourthValue;
    }
    
};

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

static void setColorGradient(unsigned int shaderProgram, vec4 color){
    //Get Uniform location
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    if(vertexColorLocation == -1){
        std::cout << "ERROR::SHADER::UNIFORM_LOCATION_FAILED" << std::endl;
    }

    //Update Uniform value
    glUseProgram(shaderProgram);
    glUniform4f(vertexColorLocation, color.x, color.y, color.z, color.w);
}

int main(){
    //Initialize GLFW and configure using Hint
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //Create a window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //Make sure GLAD is initialized and working
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }     

    //Specify viewport so opengl knows how to display data and coordinates with respect to the window
    glViewport(0, 0, 800, 600);
     
    //Everytime window is resized, callback function to edit viewport.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  


    //Vertices of a triangle
    GLfloat vertices[] = {
        -1.0f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        1.0f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f
    };  

    //  GLfloat vertices2[] = {
    //     0.5f, -0.5f, 0.0f,
    //     1.5f, -0.5f, 0.0f,
    //     0.0f,  0.5f, 0.0f
    // };  

    //Parse shaders, compile, and link
    ShaderProgramSource shaderSource = parseShader("./Shaders.GLSL");
    std::cout << shaderSource.FragmentSource << '\n';
    unsigned int shaderProgram = compileAndLinkShaders(shaderSource);

    //Create a vertext array object to manage vertext attribiutes
    unsigned int VAO;
    glGenVertexArrays(1, &VAO); 
    glBindVertexArray(VAO);

    //Create a Vertex Buffer Object (VBO) that can store large number of vertices and copy data to buffer
    //Use glGenBuffers to generate buffer of id 1 and bind it to array buffer
    unsigned int VBO;
    glGenBuffers(1, &VBO);  
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

    //Tell vertext buffer object how to interpret vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);  


    //Render loop
    while(!glfwWindowShouldClose(window)) //Checks if GLFW has been instructed to close
    {   
        //Get Random Color
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        vec4 vertexColor = vec4(0.0f, greenValue, 0.0f, 1.0f);
        setColorGradient(shaderProgram, vertexColor);

        //Draw Object
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window); //swap color buffer that is used to render 
        glfwPollEvents(); //Checks if any events has been triggered, updates window states, and calls cooresponding functions
    }

    //Clean up all of GLFW resources
    glfwTerminate();
    return 0;
}
 


//Takes in window, and new width and height. Changes viewport on resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{   
    glViewport(0, 0, width, height);
}
