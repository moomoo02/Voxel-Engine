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
};
