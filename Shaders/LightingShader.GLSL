#Shader Vertex
#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 objectColor;
void main()
{
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
#Shader Fragment
#version 330 core
uniform vec3 objectColor;
uniform vec3 lightColor;
out vec4 FragColor;
void main()
{
    FragColor = vec4(lightColor * objectColor, 1.0);

}