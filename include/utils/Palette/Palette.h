#ifndef RAVEN_ENGINE_PALETTE_H
#define RAVEN_ENGINE_PALETTE_H

#include "imgui.h"
#include <array>
#include <string>

namespace RavenEngine {

class Palette {
public:
    Palette();
    ~Palette();

    void DrawUI();
    void SetTitle(const std::string& title);
    bool CloseRequested() const;

private:
    std::array<ImVec4, 5> colors; // Stores the colors of the palette
    ImVec2 initialPos;
    std::string paletteTitle;
    bool closeRequested;

    std::array<bool, 10> locked = {false};

    void DrawColorSquares();
};

} // namespace RavenEngine

#endif // RAVEN_ENGINE_PALETTE_H