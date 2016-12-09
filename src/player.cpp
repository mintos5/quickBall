#include "player.h"
#include "scene.h"
#include "asteroid.h"
#include "object_frag.h"
#include "object_vert.h"
#include "fence.h"

#include <GLFW/glfw3.h>

Player::Player() {
  // Reset fire delay
  fireDelay = 0;
  // Set the rate of fire
  fireRate = 0.3f;
  // Fire offset;
  fireOffset = glm::vec3(0.7f,0.0f,0.0f);

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
  // Fire delay increment
  fireDelay += dt;

  // Hit detection
  for ( auto obj : scene.objects ) {
    // Ignore self in scene
    if (obj.get() == this)
      continue;

    // We only need to collide with asteroids, ignore other objects
    auto asteroid = std::dynamic_pointer_cast<fence>(obj);
    if (!asteroid) continue;

    if (glm::distance(position, asteroid->position) < asteroid->scale.y) {
      // Explode
//      auto explosion = ExplosionPtr(new Explosion{});
//      explosion->position = position;
//      explosion->scale = scale * 3.0f;
//      scene.objects.push_back(explosion);

      // Die
      return false;
    }
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
  // Firing projectiles
  if(scene.keyboard[GLFW_KEY_SPACE] && fireDelay > fireRate) {
    // Reset fire delay
    fireDelay = 0;
    // Invert file offset
    fireOffset = -fireOffset;

//    auto projectile = ProjectilePtr(new Projectile{});
//    projectile->position = position + glm::vec3(0.0f, 0.0f, 0.3f) + fireOffset;
//    scene.objects.push_back(projectile);
  }

  //std::cout << "positionZ: " << this->position.z << "positionX: " << this->position.x <<std::endl;
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