#version 330 core
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;

uniform mat2x3 model;

out vec4 Color;
out vec2 FragPos;
out vec3 Normal;

void main() {
    vec2 pos = vec3(a_position.xy, 1.0f) * model;
    gl_Position = vec4(pos, a_position.z, 1.0f);
    Color = vec4(a_color, 1.0f);
    FragPos = pos;
    Normal = vec3(0, 0, -1);
}