#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D Texture;
uniform float alpha;

void main() {
    vec4 textureColor = texture(Texture, TexCoord);
    FragColor = vec4(textureColor.rgb, textureColor.a * alpha);
}
