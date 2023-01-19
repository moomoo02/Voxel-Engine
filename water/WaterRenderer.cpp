#include "WaterRenderer.h"


WaterRenderer::WaterRenderer(WaterShader shader, WaterFrameBuffers fbos)
{
    this->shader = shader;
    this->fbos = fbos;

    //prepare VAO
    waterVAO.createVBO("water", { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 });
}

void WaterRenderer::render(std::vector<WaterTile> water, glm::mat4 view, glm::mat4 projection)
{
    prepareRender(view, projection);
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
void WaterRenderer::prepareRender(glm::mat4 view, glm::mat4 projection)
{
    shader.use();
    shader.loadViewMatrix(view);
    shader.loadProjectionMatrix(projection);
    shader.connectTextureUnits();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbos.getReflectionTexture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, fbos.getRefractionTexture());

}





