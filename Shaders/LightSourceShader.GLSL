#Shader Vertex
#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
#Shader Fragment
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0);

}