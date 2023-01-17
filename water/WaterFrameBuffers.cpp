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

int WaterFrameBuffers::createTextureAttachment(int width, int height)
{
	unsigned int texture;
    glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
				0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
				texture, 0);
	return texture;
}
