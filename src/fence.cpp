//
// Created by michal on 7.12.2016.
//

#include "fence.h"
#include "object_frag.h"
#include "object_vert.h"


fence::fence() {
    // Initialize static resources if needed
    if (!shader) shader = ShaderPtr(new Shader{object_vert, object_frag});
    if (!texture) texture = TexturePtr(new Texture{"fence.rgb", 1024, 512});
    if (!mesh) mesh = MeshPtr(new Mesh{shader, "fence.obj"});
    this->scale = glm::vec3(0.4,0.4,0.4);
    this->position.y = -1.1;
    this->position.z = -2;
    this->position.x = 0;
}

fence::~fence() {

}

bool fence::Update(Scene &scene, float dt) {
    //out of sceen
    if (this->position.z > scene.position.z+scene.OUT){
        return false;
    }
    if (glm::distance(position, scene.player->position) < scene.MIN_LENGHT) {
        std::cout << "fence" << std::endl;
        scene.playerStatus--;
        return false;
    }
    GenerateModelMatrix();
    return true;
}

void fence::Render(Scene &scene) {
    shader->Use();

    // use camera
    shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
    shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");

    // render mesh
    shader->SetMatrix(modelMatrix, "ModelMatrix");
    shader->SetTexture(texture, "Texture");
    mesh->Render();
}
// shared resources
MeshPtr fence::mesh;
ShaderPtr fence::shader;
TexturePtr fence::texture;
