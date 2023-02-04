#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//Takes in window, and new width and height.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{   
    glViewport(0, 0, width, height);
};

int main()
{
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

    //Render loop
    while(!glfwWindowShouldClose(window)) //Checks if GLFW has been instructed to close
    {
        glfwSwapBuffers(window); //swap color buffer that is used to render 
        glfwPollEvents(); //Checks if any events has been triggered, updates window states, and calls cooresponding functions
    }

    //Clean up all of GLFW resources
    glfwTerminate();

    return 0;
}