//
// Created by michal on 7.12.2016.
//

#include "enemy.h"
#include "object_frag.h"
#include "object_vert.h"

enemy::enemy() {
    // Initialize static resources if needed
    if (!shader) shader = ShaderPtr(new Shader{object_vert, object_frag});
    if (!texture) texture = TexturePtr(new Texture{"spider.rgb", 1024, 1024});
    if (!mesh) mesh = MeshPtr(new Mesh{shader, "spider.obj"});
    this->scale = glm::vec3(0.3,0.3,0.3);
    this->position.y = -1;
    this->position.z = -3;
    this->position.x = 0;
    this->worldPosition = this->position;
    this->rotation.z = 0.5f*PI;
}

enemy::enemy(bool combiAnimation) : combiAnimation(combiAnimation) {
    // Initialize static resources if needed
    if (!shader) shader = ShaderPtr(new Shader{object_vert, object_frag});
    if (!texture) texture = TexturePtr(new Texture{"spider.rgb", 1024, 1024});
    if (!mesh) mesh = MeshPtr(new Mesh{shader, "spiderAnimate1.obj"});
    this->scale = glm::vec3(0.3,0.3,0.3);
    this->position.y = -1;
    this->position.z = -3;
    this->position.x = 0;
    this->worldPosition = this->position;
    //this->rotation.z = PI/2;
}

enemy::~enemy() {

}

bool enemy::Update(Scene &scene, float dt) {
    lifeTime += dt;
    if (this->combiAnimation) {
        this->position.x = this->worldPosition.x + sin(lifeTime)*0.7;
        this->position.z = this->worldPosition.z + cos(lifeTime)*0.7;
        this->rotation.z = (PI/2)*sin(lifeTime)*animationSpeed;
    }
    else {
        if (direction==1){
            this->position.x += dt*animationSpeed;
        }
        if (direction==-1) {
            this->position.x -= dt*animationSpeed;
        }
        if (this->position.x >= 0.8){
            direction = 0;
            this->rotation.z +=dt*animationSpeed*2;
            if (this->rotation.z >= (1.5f*PI) ){
                direction = -1;
                this->rotation.z = 1.5f*PI;
            }
        }
        if (this->position.x <= - 0.8){
            direction = 0;
            this->rotation.z +=dt*animationSpeed*2;
            if (this->rotation.z >= (2.5f*PI) ){
                direction = 1;
                this->rotation.z = PI/2;
            }
        }

    }
    //out of sceen
    if (this->position.z > scene.position.z+scene.OUT){
        return false;
    }
    if (glm::distance(position, scene.player->position) < scene.MIN_LENGHT) {
        std::cout << "enemy" << std::endl;
        scene.playerStatus--;
        return false;
    }
    GenerateModelMatrix();
    return true;
}

void enemy::Render(Scene &scene) {
    shader->Use();

    // use camera
    shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
    shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");

    // render mesh
    shader->SetMatrix(modelMatrix, "ModelMatrix");
    shader->SetTexture(texture, "Texture");
    mesh->Render();
}

void enemy::setWorldPosition(const glm::vec3 &worldPosition) {
    this->worldPosition.x = worldPosition.x;
    this->worldPosition.z = worldPosition.z;
}

// shared resources
MeshPtr enemy::mesh;
ShaderPtr enemy::shader;
TexturePtr enemy::texture;
