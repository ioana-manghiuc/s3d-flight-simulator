#version 330 core
out vec4 FragColor;

in vec3 texCoords;

uniform samplerCube skybox;
uniform float colorScale;

void main()
{    
    FragColor = texture(skybox, texCoords)*colorScale;
}
