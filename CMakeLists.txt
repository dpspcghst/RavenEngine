cmake_minimum_required(VERSION 3.12)
project(RavenEngine)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find packages
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Define source files
set(PROJECT_SOURCES
    src/main.cpp

    src/Core/GLFWManagement/GLFWCallbacks.cpp
    src/Core/GLFWManagement/GLFWContextManager.cpp
    src/Core/GLFWManagement/GLFWEventPoller.cpp
    src/Core/GLFWManagement/GLFWWindowWrapper.cpp
    
    src/Core/UIManager.cpp
    src/Core/Viewport.cpp
    src/Core/Workspace.cpp
    src/Core/GameLoop.cpp
    Settings/SettingsManager.cpp

    src/Renderer/Renderer.cpp
    src/Renderer/Camera/Camera.cpp
    src/Renderer/FBO/FBManager.cpp

    src/Physics/PhysicsEngine.cpp
    src/Physics/CollisionManager.cpp
    src/Physics/CollisionPanel.cpp
    src/Physics/RigidBody.cpp
    src/Physics/RigidBodyPanel.cpp

    src/Renderer/Shaders/ShaderManager.cpp
    src/Renderer/Shaders/ShaderLoader.cpp
    src/Renderer/Shaders/ShaderProgram.cpp

    src/Renderer/Shapes/Shape.cpp
    src/Renderer/Shapes/ShapeRenderer.cpp

    src/Renderer/Shapes/Shape2D/Point.cpp
    src/Renderer/Shapes/Shape2D/Line.cpp
    src/Renderer/Shapes/Shape2D/Triangle.cpp
    src/Renderer/Shapes/Shape2D/TriQuad.cpp
    src/Renderer/Shapes/Shape2D/Rect.cpp
    src/Renderer/Shapes/Shape2D/Shape2d.cpp
    src/Renderer/Shapes/Shape2D/Circle.cpp
    src/Renderer/Shapes/Shape2D/ShapeCreate2D.cpp

    src/Renderer/Shapes/Shape3D/Mesh.cpp
    src/Renderer/Shapes/Shape3D/Shape3D.cpp
    src/Renderer/Shapes/Shape3D/Cube.cpp
    src/Renderer/Shapes/Shape3D/ShapeCreate3D.cpp

    src/Renderer/Texture/TextureFileDialog.cpp
    src/Renderer/Texture/TextureManager.cpp
    src/Renderer/Texture/TextureManagerPanel.cpp
    src/Renderer/Texture/TexturePanel.cpp
    src/Renderer/Texture/TexturePreview.cpp

    src/Renderer/UBO/UniformBuffer.cpp
    src/Renderer/UBO/UniformBufferManager.cpp
    src/Renderer/Materials/MaterialManager.cpp

    src/Scene/Scene.cpp
    src/Scene/SceneGraphRenderer.cpp
    src/Scene/SceneManager.cpp
    src/Scene/SceneNode.cpp
    src/Scene/ScenePanel.cpp
    
    src/Utils/Console.cpp
    src/Utils/FileDialog.cpp
    src/Utils/ImGuiManager.cpp
    src/Utils/MenuSystem.cpp
    src/Utils/PlayBackBar.cpp
    src/Utils/ResourceManager.cpp
    src/Utils/Inspector.cpp

    Tools/Doodle/Doodle.cpp
    Tools/Doodle/DoodleManager.cpp
    Tools/Palette/Palette.cpp
    Tools/Palette/PaletteManager.cpp
    Tools/Calc/Calculator.cpp
    Tools/Calc/CalculatorManager.cpp
)

# Add resources file for Windows
if(WIN32)
  list(APPEND PROJECT_SOURCES "resources.rc")
endif()

# Glob ImGui sources and backends
file(GLOB IMGUI_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_glfw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_opengl3.cpp"
)

# Add GLAD source
set(GLAD_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c")

# Add executable target
add_executable(RavenEngine ${PROJECT_SOURCES} ${IMGUI_SOURCES} ${GLAD_SOURCE})

# Include directories
target_include_directories(RavenEngine PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/stb"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/glm"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Core"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Core/GLFWManagement"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Utils"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/glad"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/KHR"
    "${CMAKE_CURRENT_SOURCE_DIR}/Settings"
)

# Link libraries
target_link_libraries(RavenEngine PRIVATE glfw OpenGL::GL nlohmann_json::nlohmann_json) 