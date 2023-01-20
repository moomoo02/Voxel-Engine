#ifndef __WATERSHADER_H__
#define __WATERSHADER_H__

#include "../Shader.h"
#include <string>

static const std::string SHADER_FILE = "Shaders/WaterShader.GLSL";


class WaterShader : public Shader {
    
public:
    WaterShader() : Shader(SHADER_FILE){};

    void loadProjectionMatrix(glm::mat4 projection){
        setMat4("projection", projection);
    }
    
    void loadViewMatrix(glm::mat4 view){
        setMat4("view", view);
    }
    
    void loadModelMatrix(glm::mat4 model){
        setMat4("model", model);
    }

    void loadMoveFactor(float moveFactor){
        setFloat("moveFactor", moveFactor);
    }

    void loadCameraPosition(glm::vec3 cameraPosition){
        setVec3("cameraPosition", cameraPosition);
    }

    void loadLight(glm::vec3 lightPosition, glm::vec3 lightColor){
        setVec3("lightPosition", lightPosition);
        setVec3("lightColor", lightColor);

    }
    
    void connectTextureUnits(){
        setInt("reflectionTexture", 0);
        setInt("refractionTexture", 1);
        setInt("waterDudv", 2);
        setInt("normalMap", 3);
    }
};

#endif // __WATERSHADER_H__