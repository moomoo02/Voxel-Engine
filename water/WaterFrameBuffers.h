#ifndef __WATERFRAMEBUFFER_H__
#define __WATERFRAMEBUFFER_H__

#include "Texture.h"

class WaterFrameBuffers{
    static const int REFLECTION_WIDTH = 320;
    static const int REFLECTION_HEIGHT = 180;

    static const int REFRACTION_WIDTH = 320;
    static const int REFRACTION_HEIGHT = 180;

    int reflectionFrameBuffer;
	int reflectionTexture;
	int reflectionDepthBuffer;

    int refractionFrameBuffer;
	int refractionTexture;
	int refractionDepthTexture;

    int createFrameBuffer();
    int createTextureAttachment( int width, int height);
    int createDepthTextureAttachment( int width, int height);
    void initialiseReflectionFrameBuffer();
    void initialiseRefractionFrameBuffer();

public:
    WaterFrameBuffers();
    //Geters


};
#endif // __WATERFRAMEBUFFER_H__