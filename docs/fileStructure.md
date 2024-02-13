RavenEngine
├── Assets
│   ├── Images
│   │   ├── Cursors
│   │   ├── Icons
│   │   └── LogoStuff
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
│       ├── Console.h
│       ├── FileDialog.h
│       ├── ImGuiManager.h
│       ├── Inspector.h
│       ├── MenuSystem.h
│       └── ResourceManager.h
├── Libs
│   ├── glm
│   ├── ImGui
│   ├── json
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
│   │   ├── Camera
│   │   │   ├── Camera.cpp
│   │   │   └── Camera.h
│   │   ├── FBO
│   │   │   ├── FBManager.cpp
│   │   │   └── FBManager.h
│   │   ├── Shapes
│   │   │   ├── Shape2d
│   │   │   │   ├── circle.cpp
│   │   │   │   ├── circle.h
│   │   │   │   ├── line.cpp
│   │   │   │   ├── line.h
│   │   │   │   ├── point.cpp
│   │   │   │   ├── point.h
│   │   │   │   ├── rect.cpp
│   │   │   │   ├── rect.h
│   │   │   │   ├── shape2d.cpp
│   │   │   │   ├── shape2d.h
│   │   │   │   ├── shapecreate2d.cpp
│   │   │   │   ├── shapecreate2d.h
│   │   │   │   ├── triangle.cpp
│   │   │   │   ├── triangle.h
│   │   │   │   ├── triquad.cpp
│   │   │   │   └── triquad.h
│   │   │   ├── Shape3d
│   │   │   │   ├── cone.cpp
│   │   │   │   ├── cone.h
│   │   │   │   ├── cube.cpp
│   │   │   │   ├── cube.h
│   │   │   │   ├── customObject.cpp
│   │   │   │   ├── customObject.h
│   │   │   │   ├── cylinder.cpp
│   │   │   │   ├── cylinder.h
│   │   │   │   ├── mesh.cpp
│   │   │   │   ├── mesh.h
│   │   │   │   ├── pyramid.cpp
│   │   │   │   ├── pyramid.h
│   │   │   │   ├── shape3d.cpp
│   │   │   │   ├── shape3d.h
│   │   │   │   ├── shapeCreate3d.cpp
│   │   │   │   ├── shapeCreate3d.h
│   │   │   │   ├── sphere.cpp
│   │   │   │   ├── sphere.h
│   │   │   │   ├── torus.cpp
│   │   │   │   └── torus.h
│   │   │   ├── shape.cpp
│   │   │   └── shape.h
│   │   ├── Texture
│   │   │   ├── TextureFileDialog.cpp
│   │   │   ├── TextureFileDialog.h
│   │   │   ├── TextureManager.cpp
│   │   │   ├── TextureManager.h
│   │   │   ├── TexturePanel.cpp
│   │   │   ├── TexturePanel.h
│   │   │   ├── TexturePreview.cpp
│   │   │   └── TexturePreview.h
│   │   ├── UBO
│   │   │   ├── UniformBuffer.cpp
│   │   │   ├── UniformBuffer.h
│   │   │   ├── UniformBufferManager.cpp
│   │   │   └── UniformBufferManager.h
│   │   ├── Renderer.cpp
│   │   └── Renderer.h
│   ├── Scene
│   │   ├── Scene.cpp
│   │   ├── Scene.h
│   │   ├── SceneGraphRenderer.cpp
│   │   ├── SceneGraphRenderer.h
│   │   ├── SceneManager.cpp
│   │   ├── SceneManager.h
│   │   ├── SceneNode.cpp
│   │   ├── SceneNode.h
│   │   ├── ScenePanel.cpp
│   │   └── ScenePanel.h
│   └── Utils
│       ├── Console.cpp
│       ├── FileDialog.cpp
│       ├── ImGuiManager.cpp
│       ├── Inspector.cpp
│       ├── MenuSystem.cpp
│       └── ResourceManager.cpp
├── Tools
│   ├── Calc
│   │   ├── Calculator.cpp
│   │   ├── Calculator.h
│   │   ├── CalculatorManager.cpp
│   │   └── CalculatorManager.h
│   ├── Doodle
│   │   ├── Doodle.cpp
│   │   ├── Doodle.h
│   │   ├── DoodleManager.cpp
│   │   └── DoodleManager.h
│   └── Palette
│       ├── Palette.cpp
│       ├── Palette.h
│       ├── PaletteManager.cpp
│       └── PaletteManager.h
├── CMakeLists.txt
├── README.md
└── Resources.rc