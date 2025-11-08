# playground-racegame

## Features

### Engine  
- Camera  
- Primitive Types (Planes, Lines)  
- Noise (Perlin)
- Entity Component System

### Game
- Chunk Generation
- Camera Control (Fly)

## Building

Dependency libraries
- [Engine](https://github.com/jorgekorgut/playground-engine) : Custom build engine that you need to install.

use CMakeGUI to configure and generate project files inside a build folder and specify the path to the dependency libraries.

## TODO

- Optmize Perlin Noise Call function. (GPU/CPU Parallelization).
- Add LOD (Level of Detail) for terrain.
- Add procedurally generated grass with wind effect.
- Add procedurally generated roads.
- Add the car model and implement car physics.
- Work on a better UI for the engine. (Add terrain parameters)

## References

[learnopengl.com](LearnOpenGL) - Joey de Vries
[https://austinmorlan.com/posts/entity_component_system/](Entity Component System) - Austin Morlan
[https://github.com/wwwtyro/glsl-atmosphere](glsl-atmosphere) - wwwtyro
