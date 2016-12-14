#version 150

in vec2 texcoord;
uniform sampler2D tex;
uniform vec4 color;
// The final color
out vec4 FragmentColor;

void main(void) {
  FragmentColor =vec4(1, 1, 1, texture(tex, texcoord).r)* color;
}