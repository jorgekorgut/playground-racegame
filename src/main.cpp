#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "engine/Engine.h"
#include "game/CameraMovement.h"
#include "game/Terrain.h"

int main()
{
    Engine & engine = Engine::GetInstance();

    engine.Initialize();
    
    GameObject plane;
	plane.transform.position = glm::vec3(0, 0, 0);
    plane.transform.rotation = glm::vec3(90, 0, 0);
    plane.transform.scale *= 1;
    engine.sceneManager.objects.push_back(plane);

    GameObject plane2;
	float angle = 80.0f; // Angle in degrees
    plane2.transform.position = glm::vec3(0, 0.5 * cos(glm::radians(angle)), -0.5 - 0.5 * sin(glm::radians(angle)));
	plane2.transform.rotation = glm::vec3(angle, 0, 0);
    plane2.transform.scale *= 1;
    engine.sceneManager.objects.push_back(plane2);

    engine.sceneManager.camera.Position = glm::vec3(0, 0, 5);

    Terrain terrain(plane);

    CameraMovement cameraMovement(engine.sceneManager.camera);
    engine.inputManager.Attach((Observer *)&cameraMovement);

    engine.StartLoop();

    engine.Destroy();
    return 0;
}
