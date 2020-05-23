#version 330 core
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoord;

uniform mat2x3 model;
uniform mat2x3 texture_model;

out vec2 v_texCoord;

void main() {
    vec2 pos = vec3(a_position.xy, 1.0f) * model;
    gl_Position = vec4(pos, a_position.z, 1.0f);
    v_texCoord = vec3(a_texCoord, 1.0f) * texture_model;
}