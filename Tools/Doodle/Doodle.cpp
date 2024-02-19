// doodle.cpp
// #include section
// #################
// Standard includes

// Third-party includes
#include "imgui.h"

// Raven includes
#include "Doodle.h"

namespace RavenEngine {

int Doodle::doodleCount = 0;

Doodle::Doodle() : canvasSize(500, 500), drawColor(IM_COL32(24, 24, 24, 255)), canvasColor(IM_COL32(255, 255, 224, 255)), eraseMode(false), closeRequested(false), doodleTitle("Doodle #" + std::to_string(++doodleCount)) {
    initialPos = ImVec2(100.0f, 100.0f); // Default initial position
}

Doodle::~Doodle() {}

void Doodle::SetInitialPosition(const ImVec2& position) {
    initialPos = position;
}

void Doodle::SetDoodleNumber(int number) {
    doodleNumber = number;
    SetTitle("Doodle Canvas #" + std::to_string(doodleNumber));
}

int Doodle::GetDoodleNumber() const {
    return doodleNumber;
}

void Doodle::SetTitle(const std::string& title) {
    doodleTitle = title;
}

void Doodle::DrawUI() {
    if (firstDraw) {
        ImGui::SetNextWindowPos(initialPos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(600, 600), ImGuiCond_Always);
        firstDraw = false;
    }

    bool open = true;
    if (ImGui::Begin(doodleTitle.c_str(), &open, ImGuiWindowFlags_None)) {
        if (!open) {
            closeRequested = true;
        }

        if (ImGui::Button(eraseMode ? "Draw" : "Erase")) {
            ToggleEraseMode();
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear")) {
            ClearCanvas();
        }
        ImGui::SameLine();
        // Add this in your DrawUI method, where you have your other buttons
        if (ImGui::Button(isSelecting ? "Stop Selecting" : "Start Selecting")) {
            isSelecting = !isSelecting;
        }
        // Collapsible section for lineSize slider
        if (ImGui::CollapsingHeader("Line Settings")) {
            ImGui::SliderFloat("Line Size", &lineSize, 1.0f, 10.0f, "Size: %.2f");
        }
        
        // Add color picker buttons and popups here
        if (ImGui::ColorButton("Draw Color", drawColor)) {
            ImGui::OpenPopup("draw_color_picker");
        }
        if (ImGui::BeginPopup("draw_color_picker")) {
            ImGui::ColorPicker3("Draw Color", (float*)&drawColor);
            ImGui::EndPopup();
        }

        ImGui::SameLine();

        if (ImGui::ColorButton("Canvas Color", canvasColor)) {
            ImGui::OpenPopup("canvas_color_picker");
        }
        if (ImGui::BeginPopup("canvas_color_picker")) {
            ImGui::ColorPicker3("Canvas Color", (float*)&canvasColor);
            ImGui::EndPopup();
        }
        
        ImVec2 windowSize = ImGui::GetWindowSize();
        canvasSize = ImVec2(windowSize.x, windowSize.y - 60);

        canvasPos = ImGui::GetCursorScreenPos();
        drawList = ImGui::GetWindowDrawList();
        drawList->AddRectFilled(canvasPos, ImVec2(canvasPos.x + canvasSize.x, canvasPos.y + canvasSize.y), canvasColor);

        ImGui::InvisibleButton("canvas", canvasSize);
        HandleCanvasInteraction();

        DrawLines();

        if (isSelecting) {
            if (ImGui::IsMouseClicked(1)) { // Right mouse button for selection, for example
                selectionStart = ImGui::GetMousePos();
            }

            if (ImGui::IsMouseReleased(1)) {
                selectionEnd = ImGui::GetMousePos();
                SelectStrokes();
                isSelecting = false; // Stop selecting after a selection is made
            }

            ImVec2 currentMousePos = ImGui::GetMousePos();
            drawList->AddRect(selectionStart, currentMousePos, IM_COL32(255, 255, 255, 255)); // Draw selection rectangle
        }
        
    }
    ImGui::End();
}

void Doodle::HandleCanvasInteraction() {
    if (!ImGui::IsWindowFocused()) {
        return;
    }

    ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 pointOnCanvas = ImVec2(mousePos.x - canvasPos.x, mousePos.y - canvasPos.y);

    if (isSelecting) {
        if (ImGui::IsMouseClicked(0)) { // Left mouse button for selection
            selectionStart = ImGui::GetMousePos();
        }

        if (ImGui::IsMouseReleased(0)) {
            selectionEnd = ImGui::GetMousePos();
            SelectStrokes();
            isSelecting = false; // Stop selecting after a selection is made
        }

        ImVec2 currentMousePos = ImGui::GetMousePos();
        drawList->AddRect(selectionStart, currentMousePos, IM_COL32(255, 255, 255, 255)); // Draw selection rectangle
    } else if (ImGui::IsMouseDown(0) && ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly)) {
        if (!eraseMode) {
            HandleFreeformDrawing(pointOnCanvas);
        } else {
            EraseLines(pointOnCanvas);
        }
    } else if (!selectedStrokes.empty() && ImGui::IsMouseDown(0)) {
        // Move selected strokes if mouse is dragged
        ImVec2 delta = ImGui::GetMouseDragDelta(0);
        MoveSelectedStrokes(delta);
        ImGui::ResetMouseDragDelta(0);
    } else {
        isDrawing = false;
    }
}

void Doodle::EraseLines(const ImVec2& pointOnCanvas) {
    std::vector<std::pair<ImColor, std::vector<std::pair<ImVec2, float>>>> newStrokes;
    for (auto& stroke : strokes) {
        std::vector<std::pair<ImVec2, float>> newStroke;
        for (size_t i = 0; i < stroke.second.size(); ++i) {
            float diffX = stroke.second[i].first.x - pointOnCanvas.x;
            float diffY = stroke.second[i].first.y - pointOnCanvas.y;
            if ((diffX * diffX + diffY * diffY) >= (eraseThreshold * eraseThreshold)) {
                newStroke.push_back(stroke.second[i]);
            } else if (!newStroke.empty()) {
                newStrokes.push_back({stroke.first, newStroke});
                newStroke.clear();
            }
        }
        if (!newStroke.empty()) {
            newStrokes.push_back({stroke.first, newStroke});
        }
    }
    strokes = std::move(newStrokes);
}

void Doodle::SelectStrokes() {
    selectedStrokes.clear();
    ImVec2 min = ImVec2(std::min(selectionStart.x, selectionEnd.x), std::min(selectionStart.y, selectionEnd.y));
    ImVec2 max = ImVec2(std::max(selectionStart.x, selectionEnd.x), std::max(selectionStart.y, selectionEnd.y));

    for (auto& stroke : strokes) {
        bool strokeSelected = false;
        for (size_t i = 0; i < stroke.second.size(); ++i) {
            ImVec2 point = ImVec2(canvasPos.x + stroke.second[i].first.x, canvasPos.y + stroke.second[i].first.y);
            if (point.x >= min.x && point.x <= max.x && point.y >= min.y && point.y <= max.y) {
                strokeSelected = true;
                break;
            }
        }
        if (strokeSelected) {
            selectedStrokes.push_back(stroke);
        }
    }
}

void Doodle::MoveSelectedStrokes(const ImVec2& delta) {
    for (auto& stroke : selectedStrokes) {
        for (size_t i = 0; i < stroke.second.size(); ++i) {
            stroke.second[i].first.x += delta.x;
            stroke.second[i].first.y += delta.y;
        }
    }
}

// Adjusting HandleFreeformDrawing to include line size
void Doodle::HandleFreeformDrawing(const ImVec2& pointOnCanvas) {
    if (isDrawing) {
        if (!strokes.empty() && !strokes.back().second.empty()) {
            ImVec2 lastPoint = strokes.back().second.back().first;
            if (lastPoint.x != pointOnCanvas.x || lastPoint.y != pointOnCanvas.y) {
                strokes.back().second.push_back({pointOnCanvas, lineSize});
            }
        }
    } else {
        strokes.push_back({drawColor, {{pointOnCanvas, lineSize}}});
        isDrawing = true;
    }
}

void Doodle::DrawLines() {
    for (const auto& stroke : strokes) {
        bool isSelected = std::find_if(selectedStrokes.begin(), selectedStrokes.end(), [&stroke](const auto& selectedStroke) {
            if (stroke.first != selectedStroke.first) return false;
            if (stroke.second.size() != selectedStroke.second.size()) return false;
            for (size_t i = 0; i < stroke.second.size(); ++i) {
                if (stroke.second[i].first.x != selectedStroke.second[i].first.x ||
                    stroke.second[i].first.y != selectedStroke.second[i].first.y ||
                    stroke.second[i].second != selectedStroke.second[i].second) return false;
            }
            return true;
        }) != selectedStrokes.end();

        ImColor strokeColor = isSelected ? ImColor(IM_COL32(255, 0, 0, 255)) : stroke.first; // Change color if selected

        for (size_t i = 1; i < stroke.second.size(); ++i) {
            ImVec2 p1 = ImVec2(canvasPos.x + stroke.second[i - 1].first.x, canvasPos.y + stroke.second[i - 1].first.y);
            float lineSize = stroke.second[i - 1].second; // Use the line size stored with the point
            ImVec2 p2 = ImVec2(canvasPos.x + stroke.second[i].first.x, canvasPos.y + stroke.second[i].first.y);
            drawList->AddLine(p1, p2, strokeColor, lineSize);
        }
    }
}

void Doodle::ToggleEraseMode() {
    eraseMode = !eraseMode;
}

void Doodle::SetDrawColor(const ImColor& color) {
    drawColor = color;
}

void Doodle::SetCanvasColor(const ImColor& color) {
    canvasColor = color;
}

void Doodle::ClearCanvas() {
    strokes.clear();
}

bool Doodle::CloseRequested() const {
    return closeRequested;
}

} // namespace RavenEngine