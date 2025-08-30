#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "engine/Engine.h"
#include "game/CameraMovement.h"
#include "game/Terrain.h"

int main()
{
    Engine & engine = Engine::GetInstance();

    engine.Initialize();

    engine.sceneManager.camera.Position = glm::vec3(0, 0, 5);

    Terrain terrain;

    CameraMovement cameraMovement(engine.sceneManager.camera);
    engine.inputManager.Attach((Observer *)&cameraMovement);
    engine.AttachUpdatable((Updatable*) &cameraMovement);

    engine.StartLoop();

    engine.Destroy();
    return 0;
}
