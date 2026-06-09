# Real-Time 3D Viewer — OpenGL / C++

A small real-time renderer in modern C++ and OpenGL. I built it while working through a
graphics-programming course, to get hands-on with how a real-time rendering pipeline fits
together: a render loop, lighting and normal mapping, a cubemap skybox, model loading, and a
framebuffer-based post-processing pass.

> **About this project.** This started as coursework — a good part of the structure was written
> along in class, and I then explored and extended it on my own. I'm sharing it as a record of
> the graphics concepts I've worked through and understood, not as an original engine design.

<!-- Screenshot to be added:
![Screenshot of the renderer](docs/screenshot.png)
*Real-time scene: a cubemap skybox and normal-mapped cubes, rendered off-screen and then put
through a pixelation post-processing shader.*
-->
_Screenshot coming soon._

## Techniques covered

- **Custom render loop & free-fly camera** (WASD + mouse look) on top of GLFW and glad
- **Phong lighting** (ambient / diffuse / specular) in GLSL
- **Tangent-space normal mapping** — per-vertex tangents/bitangents and a TBN matrix
- **An animated, time-driven fragment shader** (a pulsating "blood wall" surface effect)
- **Cubemap skybox**
- **Off-screen framebuffer + full-screen post-processing pass** (pixelation effect)
- **Model import via Assimp** (`.obj`)
- **RAII wrappers for OpenGL resources** — GPU handles are released automatically instead of
  scattering `glDelete*` calls through the code
- **Modern C++ (C++20)**

## Tech stack

| Area | Used |
|------|------|
| Language | C++20 |
| Graphics API | OpenGL 3.3+ (tested on a 4.6 driver) |
| Windowing / input | [GLFW](https://www.glfw.org/) |
| GL function loader | [glad](https://github.com/Dav1dde/glad) |
| Math | [GLM](https://github.com/g-truc/glm) (vendored in `glm/`) |
| Texture loading | [stb_image](https://github.com/nothings/stb) |
| Model loading | [Assimp](https://github.com/assimp/assimp) |
| Build | Visual Studio 2022 (toolset v143), dependencies via [vcpkg](https://vcpkg.io/) (manifest mode) |

## Building

> **Note:** the project builds as **x64** (it uses C++20 features that are only enabled in the
> x64 configurations).

1. Install **Visual Studio 2022** with the *Desktop development with C++* workload. This includes
   the bundled vcpkg used for dependency management.
2. Open `OpenGL_Fabian.sln`.
3. Select the **Debug | x64** or **Release | x64** configuration.
4. **Build**. On the first build, vcpkg (manifest mode, driven by [`vcpkg.json`](vcpkg.json))
   downloads and builds the dependencies — `glad`, `glfw3`, `stb` and `assimp` — automatically.
   The first run takes a few minutes because Assimp is compiled from source; later builds reuse
   the binary cache.

The required runtime DLLs and the `.glsl` shader files are copied next to the executable as part
of the build.

## Controls

| Input | Action |
|-------|--------|
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| `Space` / `Left Ctrl` | Move up / down |
| Mouse (hold **left button**) | Look around |
| `G` | Spawn a cube |

## How it fits together

- **`Engine`** owns the window, the OpenGL context and the main loop, and exposes `onCreate` /
  `onUpdate` hooks.
- **`Viewer3D`** is the concrete scene built on `Engine`: it holds the camera, the objects, the
  skybox and the post-processing framebuffer, and handles input.
- Rendering goes into an **off-screen framebuffer** first; the result is then drawn to a
  full-screen quad through the **pixelation shader** (`FB_*Shader.glsl`).
- GPU objects (buffers, textures, shader programs, framebuffers) are wrapped in a small
  **`UniqueResource`** RAII type so they clean themselves up.

Shaders live in the `*.glsl` files; textures and the skybox cubemap are in `assets/`.

## Status & notes

This is a learning project, so a few rough edges are intentional/known:

- The sample model file (`SM_Bunny01.obj`) isn't included in the repo, so model loading falls
  back gracefully and the scene starts empty — press `G` to spawn cubes that use the lighting and
  shader pipeline.
- Dependencies are managed entirely through vcpkg manifest mode; the generated `vcpkg_installed/`
  folder is intentionally **not** committed.
