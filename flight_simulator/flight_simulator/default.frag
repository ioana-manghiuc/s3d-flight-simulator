#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 crntPos;
in vec3 Normal;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 base()
{
	float ambient = 0.2f;
	
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPos - crntPos);

	float diffuse = max(dot(normal, lightDir), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDir), 0.0f), 8);
	float specular = specAmount * specularLight;

	return texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}

vec4 direcLight()
{
	float ambient = 0.20f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}

void main()
{
	FragColor = direcLight();
}