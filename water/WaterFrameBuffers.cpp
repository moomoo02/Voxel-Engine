#include "WaterFrameBuffers.h"


void WaterFrameBuffers::initialiseReflectionFrameBuffer() {
	reflectionFrameBuffer = createFrameBuffer();
	reflectionTexture = createTextureAttachment(REFLECTION_WIDTH,REFLECTION_HEIGHT);
	reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH,REFLECTION_HEIGHT);		unbindCurrentFrameBuffer();
}

WaterFrameBuffers::WaterFrameBuffers() {//call when loading the game
	initialiseReflectionFrameBuffer();
	initialiseRefractionFrameBuffer();
}

int WaterFrameBuffers::createFrameBuffer()
{
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo); 
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
}
