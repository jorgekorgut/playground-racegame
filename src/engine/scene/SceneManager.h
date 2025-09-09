#pragma once
#include "Camera.h"
#include <vector>

class SceneManager {
    public:
    SceneManager();
    void Initialize();
    void Destroy();
    void Update();
    Camera camera;
};
