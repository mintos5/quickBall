//
// Created by michal on 7.12.2016.
//

#ifndef PPGSO_HEART_H
#define PPGSO_HEART_H

#include <mesh.h>
#include <shader.h>
#include <texture.h>
#include "object.h"
#include "scene.h"

class heart : public Object {
public:
    heart();

    heart(bool combiAnimation);

    ~heart();

    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;
private:
    bool combiAnimation = false;
    float lifeTime = 0.0f;
    // Static resources (Shared between instances)
    static MeshPtr mesh;
    static ShaderPtr shader;
    static TexturePtr texture;
};
typedef std::shared_ptr<heart> HeartPtr;

#endif //PPGSO_HEART_H
