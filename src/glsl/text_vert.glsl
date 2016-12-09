#version 150

in vec4 coord;
out vec2 texcoord;

uniform mat4 projection;

void main(void) {
  texcoord = coord.zw;
  gl_Position = projection * vec4(coord.xy, 0, 1);
}