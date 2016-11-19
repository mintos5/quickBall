#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "scene.h"

#define PI 3.14159265358979323846f

Camera::Camera(float fow, float ratio, float near, float far) {
  float fowInRad = (PI/180.0f) * fow;

  projectionMatrix = glm::perspective(fowInRad, ratio, near, far);

  up = glm::vec3(0,1,0);
  position = glm::vec3(0,0,-10);
  back = glm::vec3(0,0,-1);
    translation = glm::vec3(0,0,0);

  viewMatrix = glm::lookAt(position, position-back, up);
}

Camera::~Camera() {
}

void Camera::Update(Scene &scene) {
    // Keyboard controls
    if(scene.keyboard[GLFW_KEY_A]) {
        translation.x = -0.05f;
    } else if(scene.keyboard[GLFW_KEY_D]) {
        translation.x = +0.05f;
    } else {
        translation.x = 0;
    }
    viewMatrix = glm::translate(viewMatrix, translation);
}
