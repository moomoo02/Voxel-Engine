#Shader Vertex
#version 330 core
layout (location = 0) in float vertex;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 plane;
out vec3 FragPos;
out vec3 Normal;
out vec3 Color;

void main()
{
    //Deconstruct vertex 
    int aPos = int(vertex) & ((1 << 18) - 1); //First 18 bits
    int aNormal = (int(vertex) >> 18) & ((1 << 6) - 1); //Next 6 bits
    int color = (int(vertex) >> 24) & ((1 << 2) - 1); //Next 2 bits

    //Deconstruct position integer into x, y, z components
    int x = aPos & ((1 << 6) - 1); 
    int y = ( aPos & (((1 << 6) - 1) << 6)) >> 6;
    int z = ( aPos & (((1 << 6) - 1) << 12)) >> 12;

    //Convert normal bits to normal vector [0, 1, 2] -> [0, 1, -1]
    int nx = ((( aNormal & ((1 << 2) - 1)) + 1) % 3) - 1; 
    int ny = (((( aNormal & (((1 << 2) - 1) << 2)) >> 2) + 1) % 3) - 1;
    int nz = (((( aNormal & (((1 << 2) - 1) << 4)) >> 4) + 1) % 3) - 1;

    // Convert color bits to its corresponding color
    vec3 aColor;
    if(color == 0){
        aColor = vec3(0.761,0.698,0.502);
    }else if(color == 1){
        aColor = vec3(0.04,0.44,0.15);
    }else if(color == 2){
        aColor = vec3(0.572,0.557,0.522);
    }else{
        aColor = vec3(1.0,1.0,1.0);
    }

    vec4 normalizedPos = vec4(x / 32.0 - 0.5, y / 32.0 - 0.5, z / 32.0 - 0.5, 1.0);
    vec4 worldPosition = model * normalizedPos;
    gl_ClipDistance[0] = dot(worldPosition, plane);
    gl_Position = projection * view * worldPosition;
    FragPos = vec3(model * normalizedPos);
    Normal = vec3(nx, ny, nz);
    Color = aColor;
}
#Shader Fragment
#version 330 core
in vec3 FragPos;
in vec3 Normal;  
in vec3 Color;
uniform vec3 viewPos;
uniform vec3 lightPos;  
uniform vec3 lightColor;
out vec4 FragColor;
void main()
{   
    //Find ambient lighting factor
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    //Find diffuse lighting factor
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //Find Specular lighting factor
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
    
    //Calculate result
    vec3 result = (ambient + diffuse + specular) * Color;
    FragColor = vec4(result, 1.0);
}