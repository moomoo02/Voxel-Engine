#Shader Vertex
#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 vertexColor;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = vec4(0.0980392f, 0.890196f, 0.30980f, 1.0f);
}
#Shader Fragment
#version 330 core
in vec4 vertexColor;
out vec4 FragColor;
void main()
{
    FragColor = vertexColor;
}
