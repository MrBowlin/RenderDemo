#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;
uniform vec3 lightColor;
uniform vec3 lightDirection;
uniform float ambientStrength;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 dir = normalize(lightDirection);
    float diff = max(dot(norm, dir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 ambient = ambientStrength * lightColor;

    FragColor = vec4(ambient + diffuse, 1.0) * texture(ourTexture, TexCoord);
}