#version 150
in vec3 color;
out vec4 oFragColor;

void main() {
    oFragColor.rgb = color.rgb;
}
