#ifndef PPGSO_CAMERA_H
#define PPGSO_CAMERA_H

#include <memory>

#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/detail/type_vec3.hpp>

// Simple camera object that keeps track of viewMatrix and projectionMatrix
// the projectionMatrix is by default constructed as perspective projection
// the viewMatrix is generated from up, position and front vectors on Update
class Scene;

class Camera {
public:
  Camera(float fow = 45.0f, float ratio = 1.0f, float near = 0.1f, float far = 10.0f);
  ~Camera();

  void Update(Scene &scene, float dt);

  glm::vec3 up;
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 translation;
    glm::vec3 rotation;

  glm::mat4 viewMatrix;
  glm::mat4 projectionMatrix;
};
typedef std::shared_ptr< Camera > CameraPtr;

#endif //PPGSO_CAMERA_H
