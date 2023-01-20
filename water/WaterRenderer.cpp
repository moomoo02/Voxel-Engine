#include "WaterRenderer.h"


WaterRenderer::WaterRenderer(WaterShader shader, WaterFrameBuffers fbos)
{
    this->shader = shader;
    this->fbos = fbos;
    //prepare VAO
    waterVAO.createVBO("water", { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 });
}

void WaterRenderer::render(std::vector<WaterTile> water, Camera camera, glm::mat4 projection)
{   
    prepareRender(camera, projection);
    waterVAO.bind();
    waterVAO.bindVBO("water");
    for(WaterTile tile : water){
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(tile.TILE_SIZE,1.0f, tile.TILE_SIZE));
        model = glm::translate(model, glm::vec3(tile.getX(), tile.getHeight(), tile.getZ()));

        shader.loadModelMatrix(model);
        draw(waterVAO,shader);
    }
}
void WaterRenderer::prepareRender(Camera camera, glm::mat4 projection)
{
    glm::vec3 lightPos(10.0f, 10.0f, -10.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    shader.use();
    shader.loadViewMatrix(view);
    shader.loadProjectionMatrix(projection);
    shader.loadCameraPosition(camera.Position);
    shader.loadLight(lightPos, lightColor); 
    moveFactor = WAVE_SPEED * glfwGetTime();
    moveFactor = fmod(moveFactor, 1.0f);
    shader.loadMoveFactor(moveFactor);
    shader.connectTextureUnits();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbos.getReflectionTexture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, fbos.getRefractionTexture());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, waterDudvMap.ID);
}





