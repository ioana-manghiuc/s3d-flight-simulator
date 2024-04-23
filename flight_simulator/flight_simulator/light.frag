#version 330 core

out vec4 FragColor;

uniform vec4 lightColor;
uniform float colorScale

void main()
{
	FragColor = lightColor;
}