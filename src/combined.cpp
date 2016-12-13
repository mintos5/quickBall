//
// Created by michal on 12.12.2016.
//

#include "combined.h"

combined::combined() {
    this->enemyPtr = EnemyPtr(new enemy{true});
    this->heartPtr = HeartPtr(new heart{true});
    this->position.y = -7.5;
    this->position.z = -2;
}

combined::~combined() {
}

bool combined::Update(Scene &scene, float dt) {
    this->heartPtr->position = this->position;
    bool test1 = this->heartPtr->Update(scene,dt);
    this->enemyPtr->setWorldPosition(this->heartPtr->position);
    bool test2 = this->enemyPtr->Update(scene,dt);
    if (this->position.z > scene.position.z+scene.OUT){
        return false;
    }
    if (test1 == false || test2 == false){
        return false;
    }
    return true;
}

void combined::Render(Scene &scene) {
    this->enemyPtr->Render(scene);
    this->heartPtr->Render(scene);
}



