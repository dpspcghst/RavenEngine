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
│   └── fileStructure.md
├── Include
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
├── Settings
│   ├── ProjectSettings.json
│   ├── ProjectWizard.cpp
│   ├── ProjectWizard.h
│   ├── SettingsManager.cpp
│   └── SettingsManager.h
├── Src
│   ├── Glad.c
│   ├── Main.cpp
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
│   │   ├── FBO
│   │   │   ├── FBManager.h 
│   │   |   └── FBManager.cpp
│   │   ├── Shapes
│   │   |   ├── Shapes2D
│   │   │   │   ├── Line.h 
│   │   |   |   ├── Line.cpp
│   │   │   |   ├── Plane.cpp
│   │   │   │   ├── Plane.h
│   │   │   │   ├── Point.h
│   │   │   │   ├── Shape2D.h
│   │   │   │   ├── Shape2D.cpp
│   │   │   │   ├── Triangle.h
│   │   │   │   ├── TriQuad.h
│   │   │   │   ├── Point.cpp
│   │   │   |   ├── Triangle.cpp
│   │   │   |   └── TriQuad.cpp
│   │   |   ├── ShapeManager.cpp
│   │   │   ├── ShapeManager.h
│   │   │   ├── ShapeCreate.cpp
│   │   │   └── ShapeCreate.h
│   │   ├── Renderer.h
│   │   └── Renderer.cpp
│   ├── Scene
│   │   ├── ScenePanel.h
│   │   ├── SceneManager.h
│   │   ├── SceneNode.h
│   │   ├── ScenePanel.cpp
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