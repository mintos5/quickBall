//
// Created by michal on 7.12.2016.
//

#include "enemyAnimate.h"
#include "object_frag.h"
#include "object_vert_anim.h"

enemyAnimate::enemyAnimate() {
    // Initialize static resources if needed
    if (!shader) shader = ShaderPtr(new Shader{object_vert_anim, object_frag});
    if (!texture) texture = TexturePtr(new Texture{"spider.rgb", 1024, 1024});
    std::vector<std::string> v = {"spider.obj","spiderAnimate1.obj","spiderAnimate2.obj"};
    if (!mesh) mesh = MeshAnimatePtr(new MeshAnimate{shader, v});
    this->scale = glm::vec3(0.4,0.4,0.4);
    this->position.y = -1;
    this->position.z = -3;
    this->position.x = 0;
    this->worldPosition = this->position;
    mesh->setKeyFrame(1);
    //this->rotation.z = PI/2;
}

enemyAnimate::enemyAnimate(bool combiAnimation) : combiAnimation(combiAnimation) {
    // Initialize static resources if needed
    if (!shader) shader = ShaderPtr(new Shader{object_vert_anim, object_frag});
    if (!texture) texture = TexturePtr(new Texture{"spider.rgb", 1024, 1024});
    std::vector<std::string> v = {"spider.obj"};
    if (!mesh) mesh = MeshAnimatePtr(new MeshAnimate{shader, v});
    this->scale = glm::vec3(0.5,0.5,0.5);
    this->position.y = -1;
    this->position.z = -3;
    this->position.x = 0;
    this->worldPosition = this->position;
    //this->rotation.z = PI/2;
}

enemyAnimate::~enemyAnimate() {

}

bool enemyAnimate::Update(Scene &scene, float dt) {
    lifeTime += dt;
//    this->position.x = this->worldPosition.x + sin(lifeTime)*0.7;
//    this->position.z = this->worldPosition.z + cos(lifeTime)*0.7;
//    this->rotation.z = (PI/2)*sin(lifeTime)*0.7;
    //this->rotation.z = sin(lifeTime);
    if (this->combiAnimation) {
        this->position.x = this->worldPosition.x + sin(lifeTime)*0.7;
        this->position.z = this->worldPosition.z + cos(lifeTime)*0.7;
        this->rotation.z = (PI/2)*sin(lifeTime)*0.7;
    }
    else {
        //this->position.x = this->worldPosition.x + sin(lifeTime)*0.4;
    }
    shader->SetFloat(std::abs(sin(lifeTime*2.0)),"TweenFactor");
    if (animationCount < lifeTime/(PI/2.0)){
        animationCount++;
    }
    //std::cout << animationCount << std::endl;
    if (animationCount%2==0){
        mesh->setKeyFrame(1);
    } else {
        mesh->setKeyFrame(2);
    }
    //mesh->setKeyFrame(1);
    GenerateModelMatrix();
    return true;
}

void enemyAnimate::Render(Scene &scene) {
    shader->Use();

    // use camera
    shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
    shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");

    // render mesh
    shader->SetMatrix(modelMatrix, "ModelMatrix");
    shader->SetTexture(texture, "Texture");
    mesh->Render();
}

void enemyAnimate::setWorldPosition(const glm::vec3 &worldPosition) {
    this->worldPosition.x = worldPosition.x;
    this->worldPosition.z = worldPosition.z;
}

// shared resources
MeshAnimatePtr enemyAnimate::mesh;
ShaderPtr enemyAnimate::shader;
TexturePtr enemyAnimate::texture;
