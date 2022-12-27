#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Shader.h"
#include "Texture.h"

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


// static void setColorGradient(unsigned int shaderProgram, vec4 color){
//     //Get Uniform location
//     int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//     if(vertexColorLocation == -1){
//         std::cout << "ERROR::SHADER::UNIFORM_LOCATION_FAILED" << std::endl;
//     }

//     //Update Uniform value
//     glUseProgram(shaderProgram);
//     glUniform4f(vertexColorLocation, color.x, color.y, color.z, color.w);
// }

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
        //Position            //Texture
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,    0.0f, 1.0f,
        0.5f, -0.5f, 0.0f,    1.0f, 0.0f,
        0.5f,  0.5f, 0.0f,    1.0f, 1.0f,
    };  

    //  GLfloat vertices2[] = {
    //     0.5f, -0.5f, 0.0f,
    //     1.5f, -0.5f, 0.0f,
    //     0.0f,  0.5f, 0.0f
    // };  

    //Parse shaders, compile, and link
    Shader shaderProgramClass("./Shaders.GLSL");
    unsigned int shaderProgram = shaderProgramClass.ID;

    //Textures
    Texture textureClass("./Textures/Bocchi2.jpeg");
    unsigned int texture = textureClass.ID;

    //Create a vertext array object to manage vertext attributes
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);  
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1); 

    //Render loop
    while(!glfwWindowShouldClose(window)) //Checks if GLFW has been instructed to close
    {   
        //Clear Color Buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Draw Object
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

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
