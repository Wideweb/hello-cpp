#version 330 core
in vec2 v_texCoord;

uniform sampler2D s_texture;

out vec4 v_color;

void main() {
    vec4 texture_color = texture(s_texture, v_texCoord);
    vec3 darkened = mix(vec3(texture_color.rgb), vec3(0, 0, 0), 0.1);

    v_color = texture(s_texture, v_texCoord);
}
