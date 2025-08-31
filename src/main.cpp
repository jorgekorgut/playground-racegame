#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "engine/Engine.h"
#include "game/CameraMovement.h"
#include "game/Terrain.h"
#include "game/GameManager.h"

int main()
{
    Engine & engine = Engine::GetInstance();

    engine.Initialize();

    GameManager game;
    
    engine.StartLoop();

    engine.Destroy();
    return 0;
}
