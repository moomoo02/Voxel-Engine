#Shader Vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 TexCoord;
void main()
{
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    TexCoord = aTexCoord;
}
#Shader Fragment
#version 330 core
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float blend;
out vec4 FragColor;
void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), blend);

}