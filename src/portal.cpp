//
// Created by michal on 7.12.2016.
//

#include "portal.h"
#include "object_frag_mono.h"
#include "object_vert.h"

portal::portal() {
    // Initialize static resources if needed
    if (!shader) shader = ShaderPtr(new Shader{object_vert, object_frag_mono});
    if (!texture) texture = TexturePtr(new Texture{"fence.rgb", 1024, 512});
    if (!mesh) mesh = MeshPtr(new Mesh{shader, "soccer_goal.obj"});
    this->scale = glm::vec3(0.02,0.02,0.02);
    this->position.y = -0.1;
    this->position.z = -5;
    this->position.x = 0.05;
    this->rotation.z = PI;
}

portal::~portal() {

}

bool portal::Update(Scene &scene, float dt) {
    GenerateModelMatrix();
    return true;
}

void portal::Render(Scene &scene) {
    shader->Use();

    // use camera
    shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
    shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");
    glm::vec4 color = glm::vec4(1.0f,1.0f,0.9f,1.0f);
    shader->SetVector(color,"color");

    // render mesh
    shader->SetMatrix(modelMatrix, "ModelMatrix");
    //shader->SetTexture(texture, "Texture");
    mesh->Render();
}
// shared resources
MeshPtr portal::mesh;
ShaderPtr portal::shader;
TexturePtr portal::texture;