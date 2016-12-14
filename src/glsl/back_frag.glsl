#version 150

in vec2 texcoord;
uniform sampler2D tex;
// The final color
out vec4 FragmentColor;

void main(void) {
  FragmentColor =texture(tex, texcoord);
}