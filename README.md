# playground-racegame

## Features

- Camera
- Primitive Types (Planes)

## Building

Dependency libraries
- GLFW (You need to install and specify PATH in CMake)
- GLAD (You need to install and specify PATH in CMake)
- ASSIMP (You need to install and specify PATH in CMake) Debug/Release Support
- IMGUI (Automatically installed)

charge all submodules
``` git pull --recurse-submodules ```

```mkdir build```  
```cd build```  

use CMakeGUI to configure and generate project files inside a build folder and specify the path to the dependency libraries.

## TODO

- Batch Rendering : Include all objects into a single vertex buffer and index buffer to reduce draw calls

## References

[learnopengl.com](LearnOpenGL) - Joey de Vries
