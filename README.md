# DX3D – a DirectX 11 game engine from scratch

A small C++20 engine built on **Direct3D 11** and the **Win32 API**, written as a learning project to understand
what sits underneath a game engine: windowing, the GPU pipeline, resource management and the 3D math that connects them.

The current demo renders a **vertex-coloured cube rotating in perspective**, with depth testing and frame-rate
independent animation.

<!-- Add a short screenshot or GIF here, e.g.:  ![Rotating cube](docs/demo.gif) -->

## Features

- **Win32 window and game loop** with non-blocking message pumping and delta-time updates
- **Direct3D 11 renderer**
  - device, swap chain (flip model) and depth buffer
  - commands recorded on a **deferred context** and executed as a command list every frame
  - HLSL shaders compiled at runtime; the **input layout is generated from shader reflection**
    (no hand-written `D3D11_INPUT_ELEMENT_DESC`)
- **GPU resource wrappers** with a shared base class and descriptor structs: vertex buffer, index buffer,
  constant buffer, graphics pipeline state
- **Own math library**: `Vector3`, `Vector4`, `Matrix4x4` (rotation, translation, scale, look-at, perspective)
- **Logger** with severity levels, and error macros that log and throw on failed D3D calls
- Debug builds use the D3D debug layer when it is installed, and fall back to a normal device when it is not

## Requirements

- Windows 10 or 11
- Visual Studio 2022 with the **Desktop development with C++** workload (MSVC v143, Windows SDK)
- A GPU with Direct3D 11 support

## Build and run

1. Clone the repository.
2. Open `GameEngine3D.sln` in Visual Studio.
3. Select **x64** and either **Debug** or **Release**.
4. Press **F5**.

The shader is loaded at runtime from `DX3D/Assets/Shaders/Basic.hlsl`, relative to the working directory.
Visual Studio runs the program from the project folder, which works out of the box. A post-build step also copies
`DX3D/Assets` next to the executable, so `Bin/x64/<Config>/GameEngine3D.exe` can be launched directly as well.

## Project structure

```
GameEngine3D.sln / .vcxproj
main.cpp                      Entry point: creates the Game and runs it
DX3D/
├── Assets/Shaders/           HLSL shaders (Basic.hlsl)
├── Include/DX3D/             Public headers
│   ├── Core/                 Base class, logger, shared descriptors and forward declarations
│   ├── Game/                 Game and Display
│   ├── Math/                 Vector3, Vector4, Matrix4x4, Rect
│   └── Window/Win32/         Window
└── Source/DX3D/
    ├── Core/                 Logger, Base
    ├── Game/                 Game loop (+ Win32 message pump)
    ├── Graphics/             Everything Direct3D (see below)
    └── Window/Win32/         Win32 window creation and window procedure
```

### Graphics module

| Class | Responsibility |
|---|---|
| `GraphicsEngine` | Owns the device, context and pipeline; builds the scene and draws each frame |
| `GraphicsDevice` | Creates the D3D11 device and every GPU resource; executes command lists |
| `DeviceContext` | Thin wrapper over a deferred context (clear, bind, draw, update buffers) |
| `SwapChain` | Back buffer, depth buffer and presentation |
| `ShaderBinary`, `VertexShaderSignature` | Runtime HLSL compilation and shader reflection |
| `GraphicsPipelineState` | Vertex/pixel shaders and the input layout |
| `VertexBuffer`, `IndexBuffer`, `ConstantBuffer` | GPU buffers |

## How a frame is rendered

```
Game::onInternalUpdate
 ├─ measure delta time
 ├─ GraphicsEngine::update          advance the animation clock
 └─ GraphicsEngine::render
     ├─ clear back buffer and depth buffer
     ├─ build World · View · Projection on the CPU
     ├─ upload the matrix to the constant buffer
     ├─ bind pipeline state, vertex buffer, index buffer
     └─ DrawIndexed (36 indices = 12 triangles)
          └─ GPU: position × worldViewProj → perspective divide → back-face culling
                  → depth test → pixel shader
     execute command list, present (vsync)
```

The cube is 8 vertices with a colour each and 36 indices; the GPU interpolates the colours across the faces.

## Math conventions

These match Direct3D's defaults, so matrices are uploaded to the GPU without transposing:

- row vectors multiplied on the left: `v' = v * M`, so `world * view * projection` reads in the order it is applied
- row-major storage, declared `row_major` in HLSL
- left-handed coordinate system, depth range 0 to 1
- triangles are front-facing when their vertices are **clockwise** as seen from outside (D3D11's default), and
  back faces are culled
- `Matrix4x4` is built from four `Vector4` rows and is exactly 64 bytes (checked with a `static_assert`)

## Known limitations

- The window is fixed-size; swap chain resizing is not implemented yet
- Animation pauses while the title bar is held, because Windows runs its own modal loop during a window drag
- No input handling yet, and the scene is a single hard-coded mesh

## Ideas for next steps

- Camera controls (keyboard and mouse)
- Normals and basic lighting
- Window resizing (`ResizeBuffers` and viewport update)
- Loading meshes from files (OBJ), and textures
- A small scene / entity layer

## License

MIT, see [LICENSE](LICENSE).
