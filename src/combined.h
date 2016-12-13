//
// Created by michal on 12.12.2016.
//

#ifndef PPGSO_COMBINED_H
#define PPGSO_COMBINED_H


#include "object.h"
#include "enemy.h"
#include "heart.h"

class combined  : public Object {
public:
    combined();
    ~combined();

    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;

private:
    EnemyPtr enemyPtr;
    HeartPtr heartPtr;
};
typedef std::shared_ptr<combined> CombiPtr;

#endif //PPGSO_COMBINED_H
