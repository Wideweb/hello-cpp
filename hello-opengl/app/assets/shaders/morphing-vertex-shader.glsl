#version 330 core
layout(location = 0) in vec3 from_position;
layout(location = 1) in vec3 from_color;
layout(location = 2) in vec3 to_position;
layout(location = 3) in vec3 to_color;

uniform mat2x3 model;
uniform float time;

out vec4 Color;
out vec2 FragPos;
out vec3 Normal;

void main() {
    float t = (sin(time) + 1) / 2;
    vec3 a_color = from_color + (to_color - from_color) * t;
    vec3 a_position = from_position + (to_position - from_position) * t;

    vec2 pos = vec3(a_position.xy, 1.0f) * model;
    gl_Position = vec4(pos, a_position.z, 1.0f);
    Color = vec4(a_color, 1.0f);
    FragPos = pos;
    Normal = vec3(0, 0, -1);
}