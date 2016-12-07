//
// Created by michal on 7.12.2016.
//

#ifndef PPGSO_FENCE_H
#define PPGSO_FENCE_H


#include <mesh.h>
#include <shader.h>
#include <texture.h>
#include "object.h"
#include "scene.h"

class fence  : public Object {
public:
    fence();
    ~fence();

    // Implement object interface
    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;
private:

    // Static resources (Shared between instances)
    static MeshPtr mesh;
    static ShaderPtr shader;
    static TexturePtr texture;
};
typedef std::shared_ptr<fence> FencePtr;

#endif //PPGSO_FENCE_H
