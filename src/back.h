//
// Created by michal on 9.12.2016.
//

#ifndef PPGSO_BACK_H
#define PPGSO_BACK_H
#include <mesh.h>
#include <shader.h>
#include <texture.h>
#include "object.h"
#include "scene.h"

class back  : public Object {
public:
    GLuint vao;
    GLuint vbo;

    back(int sizeX, int sizeY);
    ~back();

    // Implement object interface
    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;
private:
    void init();
    glm::mat4 projection;
    int sizeX;
    int sizeY;
    // Static resources (Shared between instances)
    static ShaderPtr shader;
    static TexturePtr texture;

};
typedef std::shared_ptr<back> BackPtr;

#endif //PPGSO_BACK_H
