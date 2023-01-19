#Shader Vertex
#version 400 core

in vec2 position;
out vec4 clipSpace;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main(void) 
{
	clipSpace = projection * view * model * vec4(position.x, -0.0, position.y, 1.0);
	gl_Position = clipSpace;
}
#Shader Fragment
#version 400 core
in vec4 clipSpace;
uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
out vec4 out_Color;


void main(void) {
	vec2 ndc = (clipSpace.xy/clipSpace.w) / 2.0 + 0.5;

	vec2 reflectTextCoords = vec2(ndc.x, -ndc.y);
	vec2 refractTexCoords = vec2(ndc.x,ndc.y);
	
	vec4 reflectColor = texture(reflectionTexture, reflectTextCoords);
	vec4 refractColor = texture(refractionTexture, refractTexCoords);

	out_Color = mix(reflectColor, refractColor, 0.5);

}