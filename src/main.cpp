#include "Engine.h"

#include "CameraMovement.h"
#include "GameManager.h"
#include "Terrain.h"

int main() {
    Engine& engine = Engine::GetInstance();

    engine.Initialize();

    GameManager game;

    engine.StartLoop();

    engine.Destroy();
    return 0;
}
