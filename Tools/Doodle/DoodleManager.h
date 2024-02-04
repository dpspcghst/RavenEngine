// doodlemanager.h
#ifndef RAVENENGINE_DOODLEMANAGER_H
#define RAVENENGINE_DOODLEMANAGER_H

// #include section
// #################
// Standard includes
#include <vector>
#include <memory>
#include <set>

// Third-party includes

// Raven includes
#include "Doodle.h"

namespace RavenEngine {

class DoodleManager {
public:
    DoodleManager();
    ~DoodleManager();

    void Update(); // Update and render all doodle windows
    void CreateNewDoodle(); // Create a new doodle window

private:
    std::vector<std::unique_ptr<Doodle>> doodles; // Stores all doodle instances
    int nextDoodleNumber; // Tracks the next number to assign
    ImVec2 nextWindowPos; // Position for the next new window

    int FindNextDoodleNumber(); // Finds the next available doodle number
    void ResetDoodleNumber(); // Resets the doodle numbering
    ImVec2 CalculateNextWindowPosition(); // Calculates the position for the next window
};

} // namespace RavenEngine

#endif // RAVENENGINE_DOODLEMANAGER_H
