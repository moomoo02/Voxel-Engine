#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <random>
#include <string>

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Chunk.h" 
#include "water/WaterRenderer.h"
#include "water/WaterFrameBuffers.h"

#include <noise/noise.h>
#include "noiseutils.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace noise;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void processInput(GLFWwindow *window);

void renderWorld(VertexArray &worldVAO, Shader worldShader, Renderer renderer, glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection, glm::vec4 plane);

static void GlClearError(){
    while (glGetError() != GL_NO_ERROR);
}

GLenum GlCheckError(std::string file, int line){
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

//Camera Variables
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
float yaw = -90.0f, pitch = 0.0f;
float lastX = 400, lastY = 300;
bool firstMouse = true;

//Initialize Camera Object
Camera camera(cameraPos, cameraUp, -90.0f, 0.0f);

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

//Lighting variables
glm::vec3 lightPos(10.0f, 10.0f, -10.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

//World variables
const int WORLD_SIZE = 5;


int main(){
    //Initialize GLFW and configure using Hint
    glfwInit();
    const char* glsl_version = "#version 100";
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //Make sure GLAD is initialized and working
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }     

    //Everytime window is resized, callback function to edit viewport.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    //Cursor moves callback
    glfwSetCursorPosCallback(window, mouse_callback); 
    glfwSetScrollCallback(window, scroll_callback); 

    std::vector<float> cube = {
        -0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f, -0.5f, 
        0.5f,  0.5f, -0.5f, 
        0.5f,  0.5f, -0.5f,  
        -0.5f,  0.5f, -0.5f,  
        -0.5f, -0.5f, -0.5f,  

        -0.5f, -0.5f,  0.5f,  
        0.5f, -0.5f,  0.5f,  
        0.5f,  0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f,  

        -0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f, -0.5f,  
        -0.5f, -0.5f, -0.5f,  
        -0.5f, -0.5f, -0.5f,  
        -0.5f, -0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,  

        0.5f,  0.5f,  0.5f,  
        0.5f,  0.5f, -0.5f,  
        0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f,  0.5f,  
        0.5f,  0.5f,  0.5f,  

        -0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f,  0.5f,  
        0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f, -0.5f,  

        -0.5f,  0.5f, -0.5f,  
        0.5f,  0.5f, -0.5f,  
        0.5f,  0.5f,  0.5f,  
        0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f, -0.5f, 
    };

    std::vector<float> cubeTexture = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

     0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
    //Parse shaders, compile, and link
    Shader worldShader("./Shaders/LightingShader.GLSL");
    Shader lightingShader("./Shaders/LightSourceShader.GLSL");
    lightingShader.use();

    //Initialize Renderer!
    Renderer renderer;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    //Create Vertex Array
    VertexArray worldVAO(VertexFormat_Normal_RGB);

    //Set up world
    std::vector<std::vector<std::unique_ptr<Chunk>>> chunks(WORLD_SIZE);
    for(int i = 0; i < WORLD_SIZE; i++){
        for(int j = 0; j < WORLD_SIZE; j++){
            std::string key = "Chunk" + std::to_string(i) + std::to_string(j);
            std::unique_ptr<Chunk> chunkPtr = std::make_unique<Chunk>();
            chunks[i].push_back(std::move(chunkPtr));
            chunks[i][j]->setupLandscape(chunks[i][j]->CHUNK_SIZE * (i+2), chunks[i][j]->CHUNK_SIZE * (j+2));
            worldVAO.createVBO(key, chunks[i][j]->render());
        }
     }

    //Set up water
    WaterShader waterShader;
    WaterRenderer waterRenderer(waterShader);
    std::vector<WaterTile> water;
    water.push_back(WaterTile(0.8f,-5.9f,-0.8f));

    //Set up Frame Buffer Object
    WaterFrameBuffers fbos;

    //Setup a test cube
    VertexArray tv(VertexFormat_Texture);
    tv.createVBO("tv", cubeTexture);
    Shader textureShader("./Shaders/TextureShader.GLSL");


    //Lighting
    VertexArray lightVAO(VertexFormat_Default);
    lightVAO.createVBO("Light", cube);
    lightVAO.bindVBO("Light");
    
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    float blend = 0.0;
    float fov = 45.0;
    float delay = glfwGetTime();
    glm::vec3 waterPos(0.8f,-5.9f,-0.8f);
    glEnable(GL_DEPTH_TEST);  

    //Texture text1("./Textures/Bocchi2.jpeg", 0);
    //Render loop
    while(!glfwWindowShouldClose(window)) //Checks if GLFW has been instructed to close
    {   
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        //Show demo window
        {
            ImGui::SliderFloat("Blend", &blend, 0.0f, 1.0f);
            ImGui::SliderFloat("FOV", &fov, 0.0f, 180.0f);
            ImGui::SliderFloat3("Light Position", glm::value_ptr(lightPos), -2.0f, 2.0f);
            ImGui::SliderFloat3("Water Position", glm::value_ptr(waterPos), -2.0f, 2.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }   

        //Input
        processInput(window);

        //Clear Color Buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //Enable Clipping Plane
        glEnable(GL_CLIP_DISTANCE0);

        //Find time calculations for camera
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        //Init transformation matrices
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 200.0f);

        //Render for fbo
        fbos.bindReflectionFrameBuffer();
        float distance = 2 * (camera.Position.y + 5.9);
        camera.Position.y -= distance;
        camera.invertPitch();
        glm::mat4 reflectionView = camera.GetViewMatrix();
        renderWorld(worldVAO, worldShader, renderer, model, reflectionView, projection, glm::vec4(0,1,0, 5.9));
        camera.Position.y += distance;
        camera.invertPitch();
        fbos.bindRefractionFrameBuffer();
        renderWorld(worldVAO, worldShader, renderer, model, view, projection, glm::vec4(0,-1,0,-5.9));
        fbos.unbindCurrentFrameBuffer();

        //Render Lighting
        lightingShader.use();
        lightVAO.bind();
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); 
        lightingShader.setMat4("model", model);
        lightingShader.setMat4("view", view);
        lightingShader.setMat4("projection", projection);
        lightVAO.bindVBO("Light");
        renderer.draw(lightVAO, lightingShader);

        //Render big tv screen
        tv.bind();
        textureShader.use();
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(20.0f));
        model = glm::translate(model, glm::vec3(1.6f,1.0f,-1.6f)); 
        textureShader.setMat4("model", model);
        textureShader.setMat4("view", view);
        textureShader.setMat4("projection", projection);
        glBindTexture(GL_TEXTURE_2D, fbos.getReflectionTexture());
        tv.bindVBO("tv");
        renderer.draw(tv, textureShader);

        //Render big tv screen
        tv.bind();
        textureShader.use();
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(20.0f));
        model = glm::translate(model, glm::vec3(3.0f,1.0f,-1.6f)); 
        textureShader.setMat4("model", model);
        textureShader.setMat4("view", view);
        textureShader.setMat4("projection", projection);
        glBindTexture(GL_TEXTURE_2D, fbos.getRefractionTexture());
        tv.bindVBO("tv");
        renderer.draw(tv, textureShader);

        //GenerateWorld
        glDisable(GL_CLIP_DISTANCE0);
        renderWorld(worldVAO, worldShader, renderer, model, view, projection, glm::vec4(0,1,0,100000));

        //Render Water
        waterRenderer.render(water, view, projection);

        //Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window); //swap color buffer that is used to render 
        glfwPollEvents(); //Checks if any events has been triggered, updates window states, and calls cooresponding functions
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
 
void renderWorld(VertexArray &worldVAO, Shader worldShader, Renderer renderer, glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection, glm::vec4 plane)  {
    worldVAO.bind();
    worldShader.use();
    worldShader.setVec4("plane", plane);
    worldShader.setMat4("view", view);
    worldShader.setMat4("projection", projection);
    worldShader.setVec3("lightPos", lightPos);  
    worldShader.setVec3("lightColor",  lightColor);
    worldShader.setVec3("viewPos", camera.Position);
    for(int i = 0; i < WORLD_SIZE; i++){
        for(int j = 0; j < WORLD_SIZE; j++){
            std::string key = "Chunk" + std::to_string(i) + std::to_string(j);
            worldVAO.bindVBO(key);

            //Draw Object
            model = glm::mat4(1.0f);

            model = glm::scale(model, glm::vec3(20,20,20));
            model = glm::translate(model, glm::vec3(i ,0.0f,-j));
            worldShader.setMat4("model", model); 

            renderer.draw(worldVAO, worldShader);
         }
    }
}

//Takes in window, and new width and height. Changes viewport on resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{   
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        camera.setGuiMode(true);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        camera.setGuiMode(false);    
    }
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset,yoffset, false);
}  

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}