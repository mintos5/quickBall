#ifndef PPGSO_MESHA_H
#define PPGSO_MESHA_H

#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "texture.h"
#include "tiny_obj_loader.h"

class MeshAnimate {
  GLuint vao;
  GLuint vbo, vko, tbo, nbo;
  GLuint ibo;
  ShaderPtr program;
  int mesh_indices_count;
  std::vector<std::vector<GLfloat>> vertexVector;

  void initGeometry(const std::vector<std::string> &obj_files);
  void initVertexVector(const std::vector<std::string> &objs);
public:
  MeshAnimate(ShaderPtr program, const std::vector<std::string> &objs);
  ~MeshAnimate();
  void Render();
  int countKeyFrame();
  void setKeyFrame(int num);
};
typedef std::shared_ptr< MeshAnimate > MeshAnimatePtr;

#endif // PPGSO_MeshAnimate_H
