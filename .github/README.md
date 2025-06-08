# Fluidus

A real-time fluid simulation using [Smoothed Particle Hydrodynamics](https://en.wikipedia.org/wiki/Smoothed-particle_hydrodynamics) (SPH) implemented in C++ and OpenGL. Parallelized to execute on multiple CPU threads using OpenMP.

![01_example](./gifs/01_example.gif)

## Setup and dependencies

Dependencies:

- GCC 11.4.0 or later
- CMake 3.12 or later
- [GLM](https://github.com/g-truc/glm)
- [GLFW3](https://www.glfw.org/)
- [GLEW](http://glew.sourceforge.net/)
- [ImGui](https://github.com/ocornut/imgui)
- [OpenMP](https://www.openmp.org/)

To install the dependencies on Ubuntu/Debian distros, you can use the following commands:

```bash
sudo apt install libglfw3-dev libglew-dev libglm-dev libomp-dev
```

To install `ImGui` run `init.sh` script in the root directory of the project. This will download ImGui v1.90.1 and copy the necessary files to the `imgui/` directory.

### Building and running

Project uses `CMake` for building. To build the project, you can use the following commands:

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE ..
make -j
```

After building the project, you can run the executable:

```bash
./fluidus
```

NOTE: This will build the project in **release** mode. If you want to build in **debug** mode, you can change the `CMAKE_BUILD_TYPE` to `DEBUG`.
In this mode the simulation is slower as it is single-threaded and not optimized.

## Controls

- **Left mouse button**: Adds force to the fluid
- **Arrow keys**: Rotate camera around container
- **Scroll**: Zoom in/out
- **Space**: Pause/Resume simulation
- **R**: Reset simulation
- **H**: Hide/Show UI
- **C**: Center camera

## Examples

Interactive container manipulation
![02_example](./gifs/02_example.gif)

Simulation Start/Stop/Resume
![03_example](./gifs/03_example.gif)

## References

- [Smoothed Particle Hydrodynamics Techniques for the Physics Based Simulation of Fluids and Solids](https://sph-tutorial.physics-simulation.org/pdf/SPH_Tutorial.pdf)
- [Particle-Based Fluid Simulation for Interactive Applications](https://matthias-research.github.io/pages/publications/sca03.pdf)
- [Particle Simulation using CUDA](https://web.archive.org/web/20140725014123/https://docs.nvidia.com/cuda/samples/5_Simulations/particles/doc/particles.pdf)
- [Smoothed Particle Hydrodynamics Real-Time Fluid Simulation Approach](https://www10.cs.fau.de/publications/theses/2010/Staubach_BT_2010.pdf)
- [Real-time particle simulation of fluids](https://old.cescg.org/CESCG-2012/papers/Horvath-Real-time_particle_simulation_of_fluids.pdf)
- [SPH - Applications of Parallel Computers (CS 5220)](https://www.cs.cornell.edu/~bindel/class/cs5220-f11/code/sph.pdf)
- [Coding Adventure: Simulating Fluids](https://www.youtube.com/watch?v=rSKMYc1CQHE)
- [The Leapfrom Algorithm](https://courses.physics.ucsd.edu/2016/Winter/physics141/Assignments/leapfrog.pdf)