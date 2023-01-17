#ifndef __WATERRENDERER_H__
#define __WATERRENDERER_H__

#include "WaterShader.h"
#include "WaterTile.h"
#include "../VertexArray.h"
#include "../Renderer.h"
#include <vector>

class WaterRenderer  : public Renderer {
    WaterShader shader;
    VertexArray waterVAO = VertexArray(VertexFormat_Water);;

    void prepareRender(glm::mat4 view, glm::mat4 projection);

public:
    WaterRenderer(WaterShader shader);
    void render(std::vector<WaterTile> water, glm::mat4 view, glm::mat4 projection);

};
#endif // __WATERRENDERER_H__