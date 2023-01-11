#Shader Vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 FragPos;
out vec3 Normal;
void main()
{
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = aNormal;
}
#Shader Fragment
#version 330 core
in vec3 FragPos;
in vec3 Normal;   
uniform vec3 lightPos;  
uniform vec3 lightColor;
out vec4 FragColor;
void main()
{
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 result = (ambient + diffuse) * norm;
    FragColor = vec4(result, 1.0);
}