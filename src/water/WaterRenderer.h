#ifndef __WATERRENDERER_H__
#define __WATERRENDERER_H__

#include "WaterShader.h"
#include "WaterTile.h"
#include "WaterFrameBuffers.h"
#include "../Texture.h"
#include "../VertexArray.h"
#include "../Renderer.h"
#include "../Camera.h"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WaterRenderer  : public Renderer {
    static constexpr float WAVE_SPEED = 0.05f;
    float moveFactor = 0.0f;

    WaterShader shader;
    VertexArray waterVAO = VertexArray(VertexFormat_Water);;
    WaterFrameBuffers fbos;
    Texture waterDudvMap = Texture( "Textures/waterdudv.png", 2);
    Texture normalMap = Texture( "Textures/NormalMap.png", 3);

    void prepareRender(Camera camera, glm::mat4 projection);

public:
    WaterRenderer(WaterShader shader, WaterFrameBuffers fbos);
    void render(std::vector<WaterTile> water, Camera camera, glm::mat4 projection);

};
#endif // __WATERRENDERER_H__