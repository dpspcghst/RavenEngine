RavenEngine
├── .vscode
├── Assets
│   └── Images
│   │   ├── Cursors
│   │   ├── Icons
│   │   └── LogoStuff
│   ├── Models
│   ├── Shaders
│   │   ├── PointFragmentShader.glsl
│   │   └── PointVertexShader.glsl
│   └── Textures
│       ├── WhiteNoiseTexture.cpp
│       └── WhiteNoiseTexture.h
├── Build
├── Docs
├── Include
│   ├── KHR
│   ├── Glad
│   ├── Components
│   │   ├── Component.h
│   │   ├── ComponentCreator.h
│   │   ├── ComponentManager.h
│   │   └── TransformComponent.h
│   ├── Core
│   │   ├── GLFWManagement
│   │   │   ├── GLFWCallbacks.h
│   │   │   ├── GLFWContextManager.h
│   │   │   ├── GLFWEventPoller.h
│   │   │   └── GLFWCWindowWrapper.h
│   │   ├── UIManager.h
│   │   ├── Viewport.h
│   │   └── Workspace.h
│   ├── glad
│   │   └── glad.h
│   ├── KHR
│   │   └── lhrplatform.h
│   ├── Maths
│   │   └── Vector3.h
│   ├── Renderer
│   │   ├── Primitives
│   │   |   ├── Line.h
│   │   |   ├── Plane.h
│   │   |   ├── Point.h
│   │   |   ├── Triangle.h
│   │   |   └── TriQuad.h
│   │   └──  Renderer.h
│   ├── Scene
│   │   ├── SceneHierarchyPanel.h
│   │   ├── SceneManager.h
│   │   └── SceneNode.h
│   └── Utils
│       ├── Doodle
│       │   ├── Doodle.h
│       │   └── DoodleManager.h
│       ├── Console.h
│       ├── FileDialog.h
│       ├── ImGuiManager.h
│       ├── Inspector.h
│       ├── MenuSystem.h
│       └── ResourceManager.h
├── Libs
│   ├── glm
│   ├── ImGui
│   └── Stb
├── Src
│   ├── Glad.c
│   ├── Main.cpp
│   ├── Components
│   │   ├── Component.cpp
│   │   ├── ComponentCreator.cpp
│   │   ├── ComponentManager.cpp
│   │   └── TransformComponent.cpp
│   ├── Core
│   │   ├── GLFWManagement
│   │   │   ├── GLFWCallbacks.cpp
│   │   │   ├── GLFWContextManager.cpp
│   │   │   ├── GLFWEventPoller.cpp
│   │   │   └── GLFWCWindowWrapper.cpp
│   │   ├── UIManager.cpp
│   │   └── Workspace.cpp
│   ├── Renderer
│   │   ├── Primitives
│   │   |   ├── Line.cpp
│   │   |   ├── Plane.cpp
│   │   |   ├── Point.cpp
│   │   |   ├── Triangle.cpp
│   │   |   └── TriQuad.cpp
│   │   ├── Renderer.cpp
│   │   └── Viewport.cpp
│   ├── Scene
│   │   ├── SceneHierarchyPanel.cpp
│   │   ├── SceneManager.cpp
│   │   └── SceneNode.cpp
│   └── Utils
│       ├── Doodle
│       │   ├── Doodle.cpp
│       │   └── DoodleManager.cpp
│       ├── Console.cpp
│       ├── FileDialog.cpp
│       ├── ImGuiManager.cpp
│       ├── Inspector.cpp
│       ├── MenuSystem.cpp
│       └── ResourceManager.cpp
├── CMakeLists.txt
├── RavenEngineProjectDoc
├── README.md
└── Resources.rc