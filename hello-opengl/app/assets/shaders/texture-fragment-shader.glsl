#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct PointLight {
    vec2 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_POINT_LIGHTS 4

in vec2 TexCoord;
in vec2 FragPos;
in vec3 Normal;

uniform int pointLightsNumber;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform sampler2D Texture;
uniform Material material;

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos);

void main() {
    vec4 result = vec4(0, 0, 0, 0);

    for (int i = 0; i < pointLightsNumber; i++)
        result += CalcPointLight(pointLights[i], Normal, vec3(FragPos, 1));

    FragColor = result;
}

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos) {
    vec3 viewDir = normalize(vec3(light.position, -1) - fragPos);
    vec3 lightDir = normalize(vec3(light.position, 0) - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(vec3(light.position, 0) - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                               light.quadratic * (distance * distance));
    // combine results
    vec4 color = texture(Texture, TexCoord);
    vec3 ambient = light.ambient * material.ambient * vec3(color);
    vec3 diffuse = light.diffuse * material.diffuse * diff * vec3(color);
    vec3 specular = light.specular * material.specular * spec * vec3(color);

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return vec4(ambient + diffuse + specular, color.a);
}
