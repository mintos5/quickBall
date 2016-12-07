#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtx/euler_angles.hpp>
#include <iostream>

#include "camera.h"
#include "scene.h"

#define PI 3.14159265358979323846f

Camera::Camera(float fow, float ratio, float near, float far) {
  float fowInRad = (PI/180.0f) * fow;

  projectionMatrix = glm::perspective(fowInRad, ratio, near, far);

  up = glm::vec3(0,1,0);
  position = glm::vec3(0,0,0);
  front = glm::vec3(0,0,1);
    translation = glm::vec3(0,0,0);

  viewMatrix = glm::lookAt(position, position-front, up);
    //viewMatrix = viewMatrix * glm::orientate4(glm::vec3(0.0,0.0,0.5));
}

Camera::~Camera() {
}

void Camera::Update(Scene &scene, float dt) {
    // Keyboard controls
    if(scene.keyboard[GLFW_KEY_A]) {
        position.x -= 10 * dt;
    } else if(scene.keyboard[GLFW_KEY_D]) {
        position.x += 10 * dt;
    } else if(scene.keyboard[GLFW_KEY_W]){
        position.z -= 10 * dt;
    } else if(scene.keyboard[GLFW_KEY_S]){
        position.z += 10 * dt;
    }
//    rotation = glm::vec3(0.0,0.0,0.0);
//    viewMatrix = glm::translate(viewMatrix, translation);
//    viewMatrix = viewMatrix * glm::orientate4(rotation);
    viewMatrix = glm::lookAt(position, position-front, up);
}
