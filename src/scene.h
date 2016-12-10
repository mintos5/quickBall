#ifndef _PPGSO_SCENE_H
#define _PPGSO_SCENE_H

#include <memory>
#include <map>
#include <list>

#include "object.h"
#include "camera.h"

// Simple object that contains all scene related data
// Object pointers are stored in a list of objects
// Keyboard and Mouse states are stored in a map and struct
class Scene {
  public:
    Scene();
    ~Scene();

    // Animate all objects in scene
    int Update(float time);
    // Render all objects in scene
    void Render();

    CameraPtr camera;
    glm::vec3 position;
    int gameStatus = 0;
    int playerStatus;
    std::list< ObjectPtr > objects;
    std::map< int, int > keyboard;
    struct {
      double x, y;
      bool left, right;
    } mouse;
};
typedef std::shared_ptr< Scene > ScenePtr;

#endif // _PPGSO_SCENE_H
