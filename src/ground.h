//
// Created by michal on 23.11.2016.
//

#ifndef PPGSO_GROUND_H
#define PPGSO_GROUND_H


#include <texture.h>
#include <shader.h>
#include <mesh.h>
#include <plane.h>
#include "object.h"

class ground : public Object{
public:
    ground();
    ground(bool ground);
    virtual ~ground();

    virtual bool Update(Scene &scene, float dt) override;

    virtual void Render(Scene &scene) override;

private:
    static PlanePtr planeR;
    static ShaderPtr shader;
    static TexturePtr texture;
};
typedef std::shared_ptr<ground> GroundPtr;


#endif //PPGSO_GROUND_H
