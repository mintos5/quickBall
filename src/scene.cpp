#include "scene.h"

Scene::Scene() {
}

Scene::~Scene() {
}

int Scene::Update(float time) {

  // Use iterator to update all objects so we can remove while iterating
  auto i = std::begin(objects);
    int num = 0;
  while (i != std::end(objects)) {
    // Update and remove from list if needed
    auto obj = i->get();
    if (!obj->Update(*this, time))
      i = objects.erase(i); // NOTE: no need to call destructors as we store shared pointers in the scene
    else
      ++i;
      num++;
  }
    camera->Update(*this,time);
    if (this->gameStatus!=0){
        int out = this->gameStatus;
        this->gameStatus = 0;
        return out;
    }
    return 0;
}

void Scene::Render() {
  // Simply render all objects
  for (auto obj : objects )
    obj->Render(*this);
}

