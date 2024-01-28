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
│   │   ├── ShaderManager.cpp
│   │   ├── ShaderManager.h
│   │   └── VertexShader.glsl
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
│   │   │   └── GLFWWindowWrapper.h
│   │   ├── UIManager.h
│   │   ├── Viewport.h
│   │   └── Workspace.h
│   ├── glad
│   │   └── glad.h
│   ├── KHR
│   │   └── khrplatform.h
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
│   ├── Core
│   │   ├── GLFWManagement
│   │   │   ├── GLFWCallbacks.cpp
│   │   │   ├── GLFWContextManager.cpp
│   │   │   ├── GLFWEventPoller.cpp
│   │   │   └── GLFWWindowWrapper.cpp
│   │   ├── UIManager.cpp
│   │   ├── Viewport.cpp
│   │   └── Workspace.cpp
│   ├── Glad.c
│   ├── Main.cpp
│   ├── Renderer
│   │   ├── FBO
│   │   │   ├── FBManager.cpp
│   │   │   └── FBManager.h
│   │   ├── Renderer.cpp
│   │   ├── Renderer.h
│   │   ├── Shapes
│   │   │   ├── Shape2D
│   │   │   │   ├── Line.cpp
│   │   │   │   ├── Line.h
│   │   │   │   ├── Plane.cpp
│   │   │   │   ├── Plane.h
│   │   │   │   ├── Point.cpp
│   │   │   │   ├── Point.h
│   │   │   │   ├── Shape2D.cpp
│   │   │   │   ├── Shape2D.h
│   │   │   │   ├── Triangle.cpp
│   │   │   │   ├── Triangle.h
│   │   │   │   ├── TriQuad.cpp
│   │   │   │   └── TriQuad.h
│   │   │   ├── ShapeCreate.cpp
│   │   │   ├── ShapeCreate.h
│   │   │   ├── ShapeManager.cpp
│   │   │   └── ShapeManager.h
│   ├── Scene
│   │   ├── SceneManager.cpp
│   │   ├── SceneManager.h
│   │   ├── SceneNode.cpp
│   │   ├── SceneNode.h
│   │   ├── ScenePanel.cpp
│   │   └── ScenePanel.h
│   └── Utils
│       ├── Console.cpp
│       ├── Calc
│       │   ├── Calculator.cpp
│       │   └── CalculatorManager.cpp
│       ├── Doodle
│       │   ├── Doodle.cpp
│       │   └── DoodleManager.cpp
│       ├── Palette
│       │   ├── Palette.cpp
│       │   └── PaletteManager.cpp
│       ├── FileDialog.cpp
│       ├── ImGuiManager.cpp
│       ├── Inspector.cpp
│       ├── MenuSystem.cpp
│       └── ResourceManager.cpp
├── CMakeLists.txt
├── README.md
└── Resources.rc