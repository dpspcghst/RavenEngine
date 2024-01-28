#ifndef RAVEN_ENGINE_PALETTE_MANAGER_H
#define RAVEN_ENGINE_PALETTE_MANAGER_H

#include "Palette.h"
#include <vector>
#include <memory>

namespace RavenEngine {

class PaletteManager {
public:
    PaletteManager();
    ~PaletteManager();

    void Update(); // Update all Palettes
    void CreateNewPalette(); // Function to create a new Palette

private:
    std::vector<std::unique_ptr<Palette>> palettes;
    // Other necessary members and functions...
};

} // namespace RavenEngine

#endif // RAVEN_ENGINE_PALETTE_MANAGER_H