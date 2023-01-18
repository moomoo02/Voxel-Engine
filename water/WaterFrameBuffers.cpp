#include "WaterFrameBuffers.h"
#include <iostream>

void WaterFrameBuffers::initialiseReflectionFrameBuffer() {
	reflectionFrameBuffer = createFrameBuffer();
	reflectionTexture = createTextureAttachment(REFLECTION_WIDTH,REFLECTION_HEIGHT);
	reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH,REFLECTION_HEIGHT);	
    std::cout << reflectionFrameBuffer << ' '<< reflectionTexture << ' ' << reflectionDepthBuffer << '\n';	
    unbindCurrentFrameBuffer();
}

void WaterFrameBuffers::initialiseRefractionFrameBuffer()
{
    refractionFrameBuffer = createFrameBuffer();
	refractionTexture = createTextureAttachment(REFRACTION_WIDTH,REFRACTION_HEIGHT);
	refractionDepthTexture = createDepthTextureAttachment(REFRACTION_WIDTH,REFRACTION_HEIGHT);
	unbindCurrentFrameBuffer();
}

WaterFrameBuffers::WaterFrameBuffers() {//call when loading the game
	initialiseReflectionFrameBuffer();
	initialiseRefractionFrameBuffer();
}

void WaterFrameBuffers::bindReflectionFrameBuffer()
{
    bindFrameBuffer(reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

void WaterFrameBuffers::bindRefractionFrameBuffer()
{
    bindFrameBuffer(refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

void WaterFrameBuffers::unbindCurrentFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0); //back to default frame buffer
	glViewport(0, 0, 1600, 1200);
}

void WaterFrameBuffers::cleanUp()
{
    glDeleteFramebuffers(1, &reflectionFrameBuffer);
    glDeleteTextures(1, &reflectionTexture);
    glDeleteRenderbuffers(1, &reflectionDepthBuffer);
    glDeleteFramebuffers(1, &refractionFrameBuffer);
    glDeleteTextures(1, &refractionTexture);
    glDeleteTextures(1, &refractionDepthTexture);
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
    //glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
	return texture;
}

int WaterFrameBuffers::createDepthTextureAttachment(int width, int height)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    //glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
    return texture;
}

int WaterFrameBuffers::createDepthBufferAttachment(int width, int height)
{
        unsigned int depthBuffer;
        glGenRenderbuffers(1, &depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
		return depthBuffer;
}

void WaterFrameBuffers::bindFrameBuffer(int frameBuffer, int width, int height){
    glBindTexture(GL_TEXTURE_2D, 0); //To make sure the texture isn't bound
    
    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl; 
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glViewport(0, 0, width, height);
}

unsigned int WaterFrameBuffers::getReflectionTexture() {
    return reflectionTexture;
}

unsigned int WaterFrameBuffers::getRefractionTexture() {
    return refractionTexture;
}

unsigned int WaterFrameBuffers::getRefractionDepthTexture() {
    return refractionDepthTexture;
}
