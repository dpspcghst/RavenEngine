// Palette.h
#ifndef RAVEN_ENGINE_PALETTE_H
#define RAVEN_ENGINE_PALETTE_H
// #include section
// #####################
// Standard includes
#include <array>
#include <string>
// Third-party includes
#include "imgui.h"
// Raven includes

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