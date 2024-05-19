#version 330 core
out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;
in vec4 fragPosLight;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform sampler2D shadowMap;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

float ShadowCalculation(vec4 fragPosLight, vec3 lightDirection, vec3 normal)
{
    vec3 projCoords = fragPosLight.xyz / fragPosLight.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    float currentDepth = projCoords.z;
    float bias = max(0.025 * (1.0 - dot(normal, lightDirection)), 0.0005);
    float shadow = currentDepth > closestDepth + bias ? 1.0 : 0.0;

    // PCF (Percentage-Closer Filtering)
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth > pcfDepth + bias ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    return shadow;
}

vec4 CalculateLighting(vec3 lightDirection, vec3 normal)
{
    float ambient = 0.2;
    float diffuse = max(dot(normal, lightDirection), 0.0);
    float specular = 0.0;
    if (diffuse != 0.0)
    {
        vec3 viewDir = normalize(camPos - crntPos);
        vec3 halfwayDir = normalize(viewDir + lightDirection);
        specular = pow(max(dot(normal, halfwayDir), 0.0), 16);
    }

    float shadow = ShadowCalculation(fragPosLight, lightDirection, normal);

    vec4 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * lightColor;
    return lighting;
}

void main()
{
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - crntPos);
    vec4 lighting = CalculateLighting(lightDirection, normal);
    FragColor = lighting * texture(diffuse0, texCoord);
}