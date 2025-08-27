#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "engine/Engine.h"
#include "game/CameraMovement.h"

int main()
{
    Engine & engine = Engine::GetInstance();

    engine.Initialize();
    
    GameObject plane;
	plane.transform.position = glm::vec3(0, -1, 0);
    plane.transform.scale *= 10;
    engine.sceneManager.objects.push_back(plane);
    engine.sceneManager.camera.Position = glm::vec3(0, 0, 5);

    CameraMovement cameraMovement(engine.sceneManager.camera);
    engine.inputManager.Attach((Observer *)&cameraMovement);

    engine.StartLoop();

    engine.Destroy();
    return 0;
}
