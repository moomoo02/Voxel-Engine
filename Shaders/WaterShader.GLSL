#Shader Vertex
#version 400 core

in vec2 position;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;
out vec4 clipSpace;
out vec2 textureCoords;
out vec3 toCameraVector;
out vec3 fromLightVector;
const float tiling = 6.0;

void main(void) 
{
	vec4 worldPosition = model * vec4(position.x, 0.0, position.y, 1.0);
	clipSpace = projection * view * worldPosition;
	gl_Position = clipSpace;
	textureCoords = vec2(position.x/2.0 + 0.5, position.y/2.0 + 0.5) * tiling;
	toCameraVector = cameraPosition - worldPosition.xyz;
	fromLightVector = worldPosition.xyz - lightPosition; 
}
#Shader Fragment
#version 400 core
in vec4 clipSpace;
in vec2 textureCoords;
in vec3 toCameraVector;
in vec3 fromLightVector;
uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D waterDudv;
uniform sampler2D normalMap;
uniform float moveFactor;
uniform vec3 lightColor;
out vec4 out_Color;

const float waveStrength = 0.015;
const float shineDamper = 20.0;
const float reflectivity = 0.6;

void main(void) {
	vec2 ndc = (clipSpace.xy/clipSpace.w) / 2.0 + 0.5;
	
	vec2 reflectTextCoords = vec2(ndc.x, -ndc.y);
	vec2 refractTexCoords = vec2(ndc.x,ndc.y);
	
	vec2 distortedTexCoords = texture(waterDudv, vec2(textureCoords.x + moveFactor*0.0, textureCoords.y)).rg*0.1;
	distortedTexCoords = textureCoords + vec2(distortedTexCoords.x, distortedTexCoords.y+moveFactor*0.0);
	vec2 totalDistortion = (texture(waterDudv, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength;

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

	vec4 normalMapColor = texture(normalMap, distortedTexCoords);
	vec3 normal = vec3(normalMapColor.r * 2.0 - 1.0, normalMapColor.b, normalMapColor.g * 2.0 - 1.0);
	normal = normalize(normal);

	vec3 reflectedLight = reflect(normalize(fromLightVector), vec3(0.0, 1.0, 0.0));
	float specular = max(dot(reflectedLight, viewVector), 0.0);
	specular = pow(specular, shineDamper);
	vec3 specularHighlights = lightColor * specular * reflectivity;

	out_Color = mix(reflectColor, refractColor, refractiveFactor);
	out_Color = mix(out_Color, vec4(0.0,0.03,0.5,1.0), 0.1) + vec4(specularHighlights,0.0);
	//out_Color = texture(waterDudv, refractTexCoords);
	//out_Color = totalDistortion;
	

}