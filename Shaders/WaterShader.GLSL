#Shader Vertex
#version 400 core

in vec2 position;
out vec4 clipSpace;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPosition;
out vec2 textureCoords;
out vec3 toCameraVector;
const float tiling = 6.0;
void main(void) 
{
	vec4 worldPosition = model * vec4(position.x, 0.0, position.y, 1.0);
	clipSpace = projection * view * worldPosition;
	gl_Position = clipSpace;
	textureCoords = vec2(position.x/2.0 + 0.5, position.y/2.0 + 0.5) * tiling;
	toCameraVector = cameraPosition - worldPosition.xyz;
}
#Shader Fragment
#version 400 core
in vec4 clipSpace;
in vec2 textureCoords;
in vec3 toCameraVector;
uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D waterDudv;
uniform float moveFactor;
out vec4 out_Color;

const float waveStrength = 0.015;
void main(void) {
	vec2 ndc = (clipSpace.xy/clipSpace.w) / 2.0 + 0.5;
	
	vec2 reflectTextCoords = vec2(ndc.x, -ndc.y);
	vec2 refractTexCoords = vec2(ndc.x,ndc.y);
	
	vec2 distortion1 = waveStrength * (texture(waterDudv, vec2(textureCoords.x + moveFactor, textureCoords.y)).rg * 2.0 - 1.0);
	vec2 distortion2 = waveStrength * (texture(waterDudv, vec2(-textureCoords.x + moveFactor, textureCoords.y + moveFactor)).rg * 2.0 - 1.0);
	vec2 totalDistortion = distortion1 + distortion2;

	reflectTextCoords += totalDistortion;
	reflectTextCoords.x = clamp(reflectTextCoords.x, 0.001,0.999);
	reflectTextCoords.y = clamp(reflectTextCoords.y, -0.999, -0.001);

	refractTexCoords += totalDistortion;
	refractTexCoords = clamp(refractTexCoords, 0.001, 0.999);

	vec4 reflectColor = texture(reflectionTexture, reflectTextCoords);
	vec4 refractColor = texture(refractionTexture, refractTexCoords);

	vec3 viewVector = normalize(toCameraVector);
	float refractiveFactor = dot(viewVector, vec3(0.0, 1.0, 0.0));
	refractiveFactor = pow(refractiveFactor, 2.0);

	out_Color = mix(reflectColor, refractColor, refractiveFactor);
	out_Color = mix(out_Color, vec4(0.0,0.03,0.5,1.0), 0.1);


}