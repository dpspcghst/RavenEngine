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
│   │   ├── SceneNode.h
│   │   └── TransformComponent.h
│   ├── Core
│   │   ├── GLFWManagement
│   │   │   ├── GLFWCallbacks.h
│   │   │   ├── GLFWContextManager.h
│   │   │   ├── GLFWEventPoller.h
│   │   │   └── GLFWCWindowWrapper.h
│   │   ├── SceneManager.h
│   │   ├── UIManager.h
│   │   ├── Viewport.h
│   │   └── Workspace.h
│   ├── Maths
│   │   └── Vector3.h
│   ├── Utils
│   │   ├── Console.h
│   │   ├── FileDialog.h
│   │   ├── ImGuiManager.h
│   │   ├── Inspector.h
│   │   ├── MenuSystem.h
│   │   ├── ResourceManager.h
│   │   └── SceneHierarchyPanel.h
│   ├── Renderer
│   │   ├── Primitives
│   │   |   └── Point.h
│   │   └──  Renderer.h
│   └── Scene
│       ├── SceneHierarchyPanel.h
│       ├── SceneManager.h
│       └── SceneNode.h
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
│   │   ├── SceneNode.cpp
│   │   └── TransformComponent.cpp
│   ├── Core
│   │   ├── GLFWManagement
│   │   │   ├── GLFWCallbacks.cpp
│   │   │   ├── GLFWContextManager.cpp
│   │   │   ├── GLFWEventPoller.cpp
│   │   │   └── GLFWCWindowWrapper.cpp
│   │   ├── SceneManager.cpp
│   │   ├── UIManager.cpp
│   │   └── Workspace.cpp
│   ├── Utils
│   │   ├── Console.cpp
│   │   ├── FileDialog.cpp
│   │   ├── ImGuiManager.cpp
│   │   ├── Inspector.cpp
│   │   ├── MenuSystem.cpp
│   │   ├── ResourceManager.cpp
│   │   └── SceneHierarchyPanel.cpp
│   ├── Renderer
│   │   ├── Primitives
│   │   |   └── Point.cpp
│   │   ├── Renderer.cpp
│   │   └── Viewport.cpp
│   └── Scene
│       ├── SceneHierarchyPanel.cpp
│       ├── SceneManager.cpp
│       └── SceneNode.cpp
├── CMakeLists.txt
├── RavenEngineProjectDoc
├── README.md
└── Resources.rc