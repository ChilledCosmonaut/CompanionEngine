#version 460 core
out vec4 fragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    float shininess;
};

uniform Material material;

void main()
{
    fragColor = texture(material.diffuse, TexCoords);
}
