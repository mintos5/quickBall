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
  scale = glm::vec3(0.3,0.3,0.3);

  //rotation = glm::vec3(0,0,1.0);

  // Initialize static resources if needed
  if (!shader) shader = ShaderPtr(new Shader{object_vert, object_frag});
  if (!texture) texture = TexturePtr(new Texture{"sphere.rgb", 256, 256});
  if (!mesh) mesh = MeshPtr(new Mesh{shader, "sphere.obj"});
}

Player::Player(CameraPtr cam){
  this->camera = cam;
    scale = glm::vec3(0.3,0.3,0.3);

  //rotation = glm::vec3(0,0,1.0);

  // Initialize static resources if needed
  if (!shader) shader = ShaderPtr(new Shader{object_vert, object_frag});
  if (!texture) texture = TexturePtr(new Texture{"lopta.rgb", 1024, 512});
  if (!mesh) mesh = MeshPtr(new Mesh{shader, "sphere.obj"});
}

Player::~Player() {
}

bool Player::Update(Scene &scene, float dt) {
    this->lifeTime +=dt;
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
        if (position.x > -0.7f){
            position.x -= turningSpeed * dt;
            rotation.y += 0.15f;
        }
    }
    if(scene.keyboard[GLFW_KEY_RIGHT]) {
        if (position.x < 0.7f){
            position.x += turningSpeed * dt;
            rotation.y -= 0.15f;
        }
    }
    if(scene.keyboard[GLFW_KEY_P]) {
        if (this->lifeTime > this->pausedTimer+0.5f){
            this->pausedTimer = this->lifeTime;
            if (paused){
                paused = false;
            }
            else{
                paused = true;
            }
        }
    }
    if(!paused){
        position.z -= this->speed * dt;
        rotation.x -= 0.15f;
        this->camera->position.z -= this->speed * dt;
    }

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

void Player::setSpeed(float speed) {
    Player::speed = speed;
}

// shared resources
MeshPtr Player::mesh;
ShaderPtr Player::shader;
TexturePtr Player::texture;