#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct SpotLight {
    vec2 position;
    vec2 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
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

#define NR_POINT_LIGHTS 8
#define NR_SPOT_LIGHTS 8

in vec4 Color;
in vec2 FragPos;
in vec3 Normal;

uniform int pointLightsNumber;
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform int spotLightsNumber;
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

uniform Material material;

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos);
vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos);

void main() {
    vec4 result = vec4(0, 0, 0, 0);

    for (int i = 0; i < pointLightsNumber; i++)
        result += CalcPointLight(pointLights[i], Normal, vec3(FragPos, 1));

    for (int i = 0; i < spotLightsNumber; i++)
        result += CalcSpotLight(spotLights[i], Normal, vec3(FragPos, 1));

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
    vec4 color = Color;
    vec3 ambient = light.ambient * material.ambient * vec3(color);
    vec3 diffuse = light.diffuse * material.diffuse * diff * vec3(color);
    vec3 specular = light.specular * material.specular * spec * vec3(color);

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return vec4(ambient + diffuse + specular, color.a);
}

vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos) {
    vec3 viewDir = normalize(vec3(light.position, -1) - fragPos);
    vec3 lightDir = normalize(vec3(light.position, 0) - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // spotlight (soft edges)
    float theta = dot(normalize(lightDir.xy), normalize(-light.direction));
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // attenuation
    float distance = length(vec3(light.position, 0) - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                               light.quadratic * (distance * distance));

    // combine results
    vec4 color = Color;
    vec3 ambient = light.ambient * material.ambient * color.rgb;
    vec3 diffuse = light.diffuse * material.diffuse * diff * color.rgb;
    vec3 specular = light.specular * material.specular * spec * color.rgb;

    ambient *= attenuation;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return vec4(ambient + diffuse + specular, color.a);
}