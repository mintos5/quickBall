//
// Created by michal on 7.12.2016.
//

#ifndef PPGSO_PORTAL_H
#define PPGSO_PORTAL_H


#include <mesh.h>
#include <shader.h>
#include <texture.h>
#include "object.h"
#include "scene.h"

class portal : public Object {

public:
    portal();
    ~portal();
    // Implement object interface
    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;
private:

    // Static resources (Shared between instances)
    static MeshPtr mesh;
    static ShaderPtr shader;
    static TexturePtr texture;
};
typedef std::shared_ptr<portal> PortalPtr;

#endif //PPGSO_PORTAL_H
