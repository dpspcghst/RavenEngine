#include "../../../include/utils/Palette/PaletteManager.h"

namespace RavenEngine {

PaletteManager::PaletteManager() {}
PaletteManager::~PaletteManager() {}

void PaletteManager::Update() {
    bool closeAll = false;

    for (auto it = palettes.begin(); it != palettes.end();) {
        (*it)->DrawUI(); // Draw the UI for each Palette
        if ((*it)->CloseRequested()) {
            closeAll = true;
            break;
        } else {
            ++it;
        }
    }

    if (closeAll) {
        palettes.clear();
    }
}

void PaletteManager::CreateNewPalette() {
    // Logic to create and manage new Palette instances
    palettes.push_back(std::make_unique<Palette>());
}

} // namespace RavenEngine
