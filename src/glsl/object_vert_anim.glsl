#version 150
// The inputs will be fed by the vertex buffer objects
in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;
in vec3 Keyframe;

// This will be passed to the fragment shader
out vec2 FragTexCoord;

// Normal to pass to the fragment shader
out vec4 normal;

// Matrices as program attributes
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform float TweenFactor;

void main() {
  // Copy the input to the fragment shader
  FragTexCoord = TexCoord;

  // Normal in world coordinates
  normal = normalize(ModelMatrix * vec4(Normal, 0.0f));

  // Calculate the final position on screen
  vec4 mixedVertex;
  mixedVertex.xyz = mix (Position,Keyframe,TweenFactor);
  mixedVertex.w = 1.0;
  gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * mixedVertex;
}
