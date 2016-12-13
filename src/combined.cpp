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
    this->heartPtr->Update(scene,dt);
    this->enemyPtr->setWorldPosition(this->heartPtr->position);
    this->enemyPtr->Update(scene,dt);
    return true;
}

void combined::Render(Scene &scene) {
    this->enemyPtr->Render(scene);
    this->heartPtr->Render(scene);
}



