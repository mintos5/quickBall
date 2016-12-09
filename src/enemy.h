//
// Created by michal on 7.12.2016.
//

#ifndef PPGSO_ENEMY_H
#define PPGSO_ENEMY_H


#include <mesh.h>
#include <shader.h>
#include <texture.h>
#include "object.h"
#include "scene.h"

class enemy  : public Object {
public:
    enemy();
    ~enemy();

    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;
private:

    // Static resources (Shared between instances)
    static MeshPtr mesh;
    static ShaderPtr shader;
    static TexturePtr texture;
};
typedef std::shared_ptr<enemy> EnemyPtr;

#endif //PPGSO_ENEMY_H
