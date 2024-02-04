#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Utils/MenuSystem.h"
#include "ImGuiManager.h"
#include "Workspace.h"
#include "FileDialog.h"
#include <iostream>
#include "../../../Tools/Doodle/DoodleManager.h"
#include "../../../Tools/Palette/Palette.h"
#include "../../../Tools/Calc/CalculatorManager.h"

using namespace RavenEngine;

MenuSystem::MenuSystem(Workspace& workspace, GLFWwindow* window, DoodleManager& doodleManager, PaletteManager& paletteManager, CalculatorManager& calculatorManager, UIManager& uiManager)
    : workspace(workspace), mainWindow(window), doodleManager(doodleManager), paletteManager(paletteManager), calculatorManager(calculatorManager), uiManager(uiManager) {
    // constructor body
}

void MenuSystem::createMainMenu() {
    if (ImGui::BeginMainMenuBar()) {
        createFileMenu();
        createToolsMenu();
        ImGui::EndMainMenuBar();
    }
    handleFileDialog(); // Call this after the main menu bar

    // output "Rendering MenuSystem..."
    //std::cout << "Rendering MenuSystem..." << std::endl;
}

void MenuSystem::createFileMenu() {
    if (ImGui::BeginMenu("File")) {
        handleFileMenuItems();
        ImGui::EndMenu();
    }
}

void MenuSystem::createToolsMenu() {
    if (ImGui::BeginMenu("Tools")) {
        handleToolsMenuItems();
        ImGui::EndMenu();
    }
}

void MenuSystem::handleFileMenuItems() {
    if (!fileDialogOpen) { // Only show these items if the file dialog is not open
        if (ImGui::MenuItem("New Project")) {
            std::cout << "New Project selected.\n";
            // New project creation logic here
        }

        if (ImGui::MenuItem("Open")) {
            std::cout << "Open selected. Opening file dialog...\n";
            fileDialogOpen = true; // Set the flag to open the file dialog
        }

        if (ImGui::MenuItem("Save")) {
            std::cout << "Save selected.\n";
            // Save current project logic here
        }

        if (ImGui::MenuItem("Exit")) {
            std::cout << "Exit selected. Closing window...\n";
            glfwSetWindowShouldClose(mainWindow, GLFW_TRUE);
        }
    }
}

void MenuSystem::handleFileDialog() {
    if (fileDialogOpen) {
        std::string filePath = FileDialog::OpenFileDialog(mainWindow);
        if (!filePath.empty()) {
            std::cout << "File selected: " << filePath << std::endl;
            // Handle the file path
            fileDialogOpen = false; // Close the dialog after handling the file
        }
        else {
            std::cout << "File dialog closed without selecting a file." << std::endl;
            // If the dialog was closed without selecting a file
            fileDialogOpen = false;
        }
    }
}

void MenuSystem::handleToolsMenuItems() {
    if (ImGui::MenuItem("Doodle")) {
        std::cout << "Doodle Selected.\n";
        doodleManager.CreateNewDoodle(); // Create a new Doodle window directly
    }

    if (ImGui::MenuItem("Palette")) {
        std::cout << "Palette Selected.\n";
        paletteManager.CreateNewPalette(); // Create a new Palette window directly
    }

    if (ImGui::MenuItem("Calculator")) {
        std::cout << "Calculator Selected.\n";
        calculatorManager.ToggleCalculatorVisibility(); // Toggle the visibility of the calculator when the "Calculator" menu item is selected
    }

    if (ImGui::MenuItem("Debug (coming soon)")) {
        std::cout << "Debug Selected.\n";
        // some debug tool or some shit
    }

    // Add more tools as needed
}