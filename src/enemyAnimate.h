//
// Created by michal on 7.12.2016.
//

#ifndef PPGSO_ENEMYA_H
#define PPGSO_ENEMYA_H


#include <mesh.h>
#include <shader.h>
#include <texture.h>
#include <meshAnimate.h>
#include "object.h"
#include "scene.h"

class enemyAnimate  : public Object {
public:
    enemyAnimate();

    enemyAnimate(bool combiAnimation);

    ~enemyAnimate();

    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;
    void setWorldPosition(const glm::vec3 &worldPosition);

private:
    float lifeTime = 0.0f;
    glm::vec3 worldPosition;
    bool combiAnimation = false;
    int animationCount = 0;
    // Static resources (Shared between instances)
    static MeshAnimatePtr mesh;
    static ShaderPtr shader;
    static TexturePtr texture;
};
typedef std::shared_ptr<enemyAnimate> EnemyAnimPtr;

#endif //PPGSO_ENEMYA_H
