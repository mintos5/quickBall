#include "player.h"
#include "scene.h"
#include "object_frag.h"
#include "object_vert.h"
#include "fence.h"
#include "enemy.h"
#include "enemyAnimate.h"
#include "heart.h"

#include <GLFW/glfw3.h>

Player::Player() {

  // Scale the default model
  scale *= 3.0f;

  //rotation = glm::vec3(0,0,1.0);

  // Initialize static resources if needed
  if (!shader) shader = ShaderPtr(new Shader{object_vert, object_frag});
  if (!texture) texture = TexturePtr(new Texture{"sphere.rgb", 256, 256});
  if (!mesh) mesh = MeshPtr(new Mesh{shader, "sphere.obj"});
}

Player::Player(CameraPtr cam){
  this->camera = cam;
  scale *= 3.0f;

  //rotation = glm::vec3(0,0,1.0);

  // Initialize static resources if needed
  if (!shader) shader = ShaderPtr(new Shader{object_vert, object_frag});
  if (!texture) texture = TexturePtr(new Texture{"lopta.rgb", 1024, 512});
  if (!mesh) mesh = MeshPtr(new Mesh{shader, "sphere.obj"});
}

Player::~Player() {
}

bool Player::Update(Scene &scene, float dt) {
    //TODO do sceny posielat gameStatus playerStatus,pridat tu zrychlovanie lopticky.
    //How much lives I have?
    if (scene.playerStatus<=0){
        scene.gameStatus = scene.GAME_OVER;
        return false;
    }
    // Keyboard controls
    if(scene.keyboard[GLFW_KEY_UP]) {
        position.z -= 5 * dt;
        rotation.x -= 0.15f;
        this->camera->position.z -= 5 * dt;
        //this->camera->Update(scene,0.0f);
    }
    if(scene.keyboard[GLFW_KEY_DOWN]) {
        position.z += 5 * dt;
        rotation.x += 0.15f;
        this->camera->position.z += 5 * dt;
        //this->camera->Update(scene,0.0f);
    }
    if(scene.keyboard[GLFW_KEY_LEFT]) {
        position.x -= 2 * dt;
        rotation.y += 0.15f;
    }
    if(scene.keyboard[GLFW_KEY_RIGHT]) {
        position.x += 2 * dt;
        rotation.y -= 0.15f;
    }
    //std::cout << "positionZ: " << this->position.z << std::endl;

    //std::cout << "positionZ: " << this->position.z << "positionX: " << this->position.x <<std::endl;

    //sending destructor location
    scene.position.z = this->position.z;
    GenerateModelMatrix();
    return true;
}

void Player::Render(Scene &scene) {
  shader->Use();

  // use camera
  shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
  glm::vec3 up = glm::vec3(0,1,0);
  glm::vec3 position2 = glm::vec3(0,0,0);
  glm::vec3 front = glm::vec3(0,0,1);

  glm::mat4 specialViewMatrix = glm::lookAt(position2, position2-front, up);
  shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");

  // render mesh
  shader->SetMatrix(modelMatrix, "ModelMatrix");
  shader->SetTexture(texture, "Texture");
  mesh->Render();
}

// shared resources
MeshPtr Player::mesh;
ShaderPtr Player::shader;
TexturePtr Player::texture;