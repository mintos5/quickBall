//
// Created by michal on 7.12.2016.
//

#include "heart.h"
#include "object_frag_mono.h"
#include "object_vert.h"

heart::heart() {
    // Initialize static resources if needed
    if (!shader) shader = ShaderPtr(new Shader{object_vert, object_frag_mono});
    if (!texture) texture = TexturePtr(new Texture{"fence.rgb", 1024, 512});
    if (!mesh) mesh = MeshPtr(new Mesh{shader, "heart.obj"});
    this->scale = glm::vec3(3,3,3);
    this->position.y = -5.7;
    this->position.z = -2;
}

heart::~heart() {

}

bool heart::Update(Scene &scene, float dt) {
    GenerateModelMatrix();
    return true;
}

void heart::Render(Scene &scene) {
    shader->Use();

    // use camera
    shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
    shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");
    glm::vec4 color = glm::vec4(1.0f,0.0f,0.0f,1.0f);
    shader->SetVector(color,"color");


    // render mesh
    shader->SetMatrix(modelMatrix, "ModelMatrix");
    //shader->SetTexture(texture, "Texture");
    mesh->Render();
}
// shared resources
MeshPtr heart::mesh;
ShaderPtr heart::shader;
TexturePtr heart::texture;
