#version 330 core
layout(location = 0) in vec3 from_position;
layout(location = 1) in vec3 from_color;
layout(location = 2) in vec3 to_position;
layout(location = 3) in vec3 to_color;

uniform mat4 MVP;
uniform float time;

out vec3 v_color;

void main() {
    float t = (sin(time) + 1) / 2;
    v_color = from_color + (to_color - from_color) * t;
    vec3 a_position = from_position + (to_position - from_position) * t;

    gl_Position = MVP * vec4(a_position, 1.0f);
}