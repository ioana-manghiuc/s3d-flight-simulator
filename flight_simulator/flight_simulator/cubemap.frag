#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform samplerCube skybox;

void main()
{
    vec3 I = normalize(FragPos);
    vec3 R = reflect(I, normalize(Normal));
    FragColor = texture(skybox, R);
}
