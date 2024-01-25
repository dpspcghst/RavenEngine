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
    Settings/SettingsManager.cpp
    Assets/Shaders/ShaderManager.cpp
    src/Core/GLFWManagement/GLFWCallbacks.cpp
    src/Core/GLFWManagement/GLFWContextManager.cpp
    src/Core/GLFWManagement/GLFWEventPoller.cpp
    src/Core/GLFWManagement/GLFWWindowWrapper.cpp
    src/Core/UIManager.cpp
    src/Core/Viewport.cpp
    src/Core/Workspace.cpp
    src/main.cpp
    src/Renderer/Shapes/Shape2D/Point.cpp
    src/Renderer/Shapes/Shape2D/Line.cpp
    src/Renderer/Shapes/Shape2D/Triangle.cpp
    src/Renderer/Shapes/Shape2D/TriQuad.cpp
    src/Renderer/Shapes/Shape2D/Plane.cpp
    src/Renderer/Shapes/Shape2D/Shape2d.cpp
    src/Renderer/Shapes/Shape.cpp
    src/Renderer/Shapes/ShapeManager.cpp
    src/Renderer/Shapes/ShapeCreate.cpp
    src/Renderer/Shapes/Mesh.cpp
    src/Renderer/Camera.cpp
    src/Renderer/Renderer.cpp
    src/Renderer/FBO/FBManager.cpp
    src/Scene/SceneManager.cpp
    src/Scene/ScenePanel.cpp
    src/Scene/SceneNode.cpp
    src/Utils/Console.cpp
    src/Utils/FileDialog.cpp
    src/Utils/ImGuiManager.cpp
    src/Utils/MenuSystem.cpp
    src/Utils/ResourceManager.cpp
    src/Utils/Inspector.cpp
    src/Utils/Doodle/Doodle.cpp
    src/Utils/Doodle/DoodleManager.cpp
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
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Core"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Core/GLFWManagement"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Utils"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Renderer"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/SceneManager" 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/glad"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/KHR"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/glm"
    "${CMAKE_CURRENT_SOURCE_DIR}/Settings"
)

# Link libraries
target_link_libraries(RavenEngine PRIVATE glfw OpenGL::GL nlohmann_json::nlohmann_json) 