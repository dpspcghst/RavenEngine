#include "Doodle/Doodle.h"
#include "imgui.h"

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
    }
    ImGui::End();
}

void Doodle::HandleCanvasInteraction() {
    // The original interaction code without cursor handling
    ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 pointOnCanvas = ImVec2(mousePos.x - canvasPos.x, mousePos.y - canvasPos.y);

    if (ImGui::IsMouseDown(0) && ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly)) {
        if (!eraseMode) {
            HandleFreeformDrawing(pointOnCanvas);
        } else {
            EraseLines(pointOnCanvas);
        }
    } else {
        isDrawing = false;
    }
}


void Doodle::EraseLines(const ImVec2& pointOnCanvas) {
    std::vector<std::pair<ImColor, std::vector<ImVec2>>> newStrokes;
    for (auto& stroke : strokes) {
        std::vector<ImVec2> newStroke;
        for (size_t i = 0; i < stroke.second.size(); ++i) {
            float diffX = stroke.second[i].x - pointOnCanvas.x;
            float diffY = stroke.second[i].y - pointOnCanvas.y;
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

void Doodle::HandleFreeformDrawing(const ImVec2& pointOnCanvas) {
    if (isDrawing) {
        // Add point to the current stroke
        if (!strokes.empty() && !strokes.back().second.empty()) {
            ImVec2 lastPoint = strokes.back().second.back();
            if (lastPoint.x != pointOnCanvas.x || lastPoint.y != pointOnCanvas.y) {
                strokes.back().second.push_back(pointOnCanvas);
            }
        }
    } else {
        // Start a new stroke with the current draw color
        strokes.push_back({drawColor, {pointOnCanvas}});
        isDrawing = true;
    }
}

void Doodle::DrawLines() {
    for (const auto& stroke : strokes) {
        for (size_t i = 1; i < stroke.second.size(); ++i) {
            ImVec2 p1 = ImVec2(canvasPos.x + stroke.second[i - 1].x, canvasPos.y + stroke.second[i - 1].y);
            ImVec2 p2 = ImVec2(canvasPos.x + stroke.second[i].x, canvasPos.y + stroke.second[i].y);
            drawList->AddLine(p1, p2, stroke.first, 1.0f); // Use the stroke's color
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