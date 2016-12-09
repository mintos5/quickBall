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
    this->position.y = -1.1;
    this->position.z = -3;
    this->position.x = 0;
}

enemy::~enemy() {

}

bool enemy::Update(Scene &scene, float dt) {
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
// shared resources
MeshPtr enemy::mesh;
ShaderPtr enemy::shader;
TexturePtr enemy::texture;
