#Shader Vertex
#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 vertexColor;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = gl_Position;
}
#Shader Fragment
#version 330 core
in vec4 vertexColor;
out vec4 FragColor;
void main()
{
    FragColor = vertexColor;
}