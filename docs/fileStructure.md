RavenEngine
├── .vscode
├── Assets
│   ├── Images
│   │   ├── Cursors
│   │   ├── Icons
│   │   └── LogoStuff
│   ├── Models
│   ├── Shaders
│   │   ├── FragmentShader.glsl
│   │   ├── VertexShader.glsl
│   │   ├── ShaderManager.cpp
│   │   └── ShaderManager.h
│   └── Textures
├── Build
├── Docs
├── Include
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
│   │   ├── Shapes
│   │   |   ├── Line.h
│   │   |   ├── Plane.h
│   │   |   ├── Point.h
│   │   |   ├── Shape.h
│   │   |   ├── ShapeManager.h
│   │   |   ├── Triangle.h
│   │   |   └── TriQuad.h
│   │   └──  Renderer.h
│   ├── Scene
│   │   ├── ScenePanel.h
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
│   │   ├── Viewport.cpp
│   │   └── Workspace.cpp
│   ├── Renderer
│   │   ├── Shapes
│   │   |   ├── Line.cpp
│   │   |   ├── Plane.cpp
│   │   |   ├── Point.cpp
│   │   |   ├── Shape.cpp
│   │   |   ├── ShapeManager.cpp
│   │   |   ├── Triangle.cpp
│   │   |   └── TriQuad.cpp
│   │   └── Renderer.cpp
│   ├── Scene
│   │   ├── ScenePanel.cpp
│   │   ├── SceneManager.cpp
│   │   └── SceneNode.cpp
│   ├── Settings
│   │   ├── ProjectSettings.json
│   │   ├── ProjectWizard.cpp
│   │   ├── ProjectWizard.h
│   │   ├── SettingsManager.cpp
│   │   └── SettingsManager.h
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