#Shader Vertex
#version 400 core

in vec2 position;

out vec2 textureCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main(void) {

	gl_Position = projection * view * model * vec4(position.x, -0.0, position.y, 1.0);
	textureCoords = vec2(position.x/2.0 + 0.5, position.y/2.0 + 0.5);
 
}
#Shader Fragment
#version 400 core

in vec2 textureCoords;

out vec4 out_Color;


void main(void) {

	out_Color = vec4(0.0, 0.0, 1.0, 1.0);

}