// doodle.h
#ifndef RAVENENGINE_DOODLE_H
#define RAVENENGINE_DOODLE_H
// #include section
// #################
// Standard includes
#include <vector>
#include <string>

// Third-party includes
#include <imgui.h>

// Raven includes

namespace RavenEngine {

class Doodle {
public:
    Doodle();
    ~Doodle();

    void DrawUI(); // Main method to draw the Doodle UI
    void ToggleEraseMode(); // Toggles between drawing and erasing
    void HandleCanvasInteraction(); // Handles drawing logic
    void HandleFreeformDrawing(const ImVec2& pointOnCanvas); // Handles freeform drawing logic
    void ClearCanvas(); // Clears the canvas
    bool CloseRequested() const; // Check if a close has been requested
    void SetTitle(const std::string& title);
    void SetDoodleNumber(int number);
    int GetDoodleNumber() const;
    void SetInitialPosition(const ImVec2& position); // Set the initial position for the Doodle window
    void SetDrawColor(const ImColor& color);
    void SetCanvasColor(const ImColor& color);
    void SetLineSize(float size) { lineSize = size; }
    void SelectStrokes();
    void MoveSelectedStrokes(const ImVec2& delta);

private:
    static int doodleCount; // Static counter for unique ID assignment
    ImVec2 initialPos; // Initial position of the Doodle window
    ImVec2 canvasSize; // Size of the drawing canvas
    ImColor drawColor; // Current drawing color
    ImColor canvasColor; // Background color of the canvas
    bool eraseMode; // Whether erasing mode is enabled
    bool closeRequested; // Whether a request to close the window has been made
    std::string doodleTitle; // Title of the Doodle window
    std::vector<std::pair<ImColor, std::vector<std::pair<ImVec2, float>>>> strokes;
    ImVec2 canvasPos; // Position of the canvas
    ImDrawList* drawList; // Draw list for ImGui
    void EraseLines(const ImVec2& point); // Method to handle erasing on the canvas
    void DrawLines(); // Method to draw lines based on points
    bool isDrawing = false; // Whether the user is currently drawing
    const float eraseThreshold = 10.0f; // Threshold for erasing strokes
    int doodleNumber; // Unique number for each doodle
    bool firstDraw = true;
    float lineSize = 1.0f; // Size of the lines drawn

    bool isSelecting = false;
    ImVec2 selectionStart, selectionEnd;
    std::vector<std::pair<ImColor, std::vector<std::pair<ImVec2, float>>>> selectedStrokes;
};

} // namespace RavenEngine

#endif // RAVENENGINE_DOODLE_H