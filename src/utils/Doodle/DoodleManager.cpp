// DoodleManager.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>

// Third-party library includes

// Raven includes
#include "../../include/utils/Doodle/DoodleManager.h"

namespace RavenEngine {

DoodleManager::DoodleManager() : nextWindowPos(100.0f, 100.0f) {
    // Initialization code for DoodleManager
    //std::cout << "Initializing DoodleManager..." << std::endl;
}

DoodleManager::~DoodleManager() = default;

void DoodleManager::Update() {
    for (auto it = doodles.begin(); it != doodles.end();) {
        (*it)->DrawUI();
        if ((*it)->CloseRequested()) {
            it = doodles.erase(it);
        } else {
            ++it;
        }
    }
    if (doodles.empty()) {
        ResetDoodleNumber();
        nextWindowPos = ImVec2(100.0f, 100.0f); // Reset position when all doodles are closed
    }
}

void DoodleManager::CreateNewDoodle() {
    int doodleNumber = FindNextDoodleNumber();
    auto doodle = std::make_unique<Doodle>();
    doodle->SetDoodleNumber(doodleNumber);
    doodle->SetInitialPosition(nextWindowPos); // Set the initial position
    doodles.push_back(std::move(doodle));
    nextWindowPos = CalculateNextWindowPosition(); // Calculate the position for the next window
}

int DoodleManager::FindNextDoodleNumber() {
    std::set<int> existingNumbers;
    for (const auto& doodle : doodles) {
        existingNumbers.insert(doodle->GetDoodleNumber());
    }

    int nextNumber = 1;
    while (existingNumbers.find(nextNumber) != existingNumbers.end()) {
        nextNumber++;
    }
    return nextNumber;
}

void DoodleManager::ResetDoodleNumber() {
    nextDoodleNumber = 1;
}

ImVec2 DoodleManager::CalculateNextWindowPosition() {
    // Increment position for cascading effect
    const float offset = 20.0f; // Offset for cascading
    ImVec2 newPos = ImVec2(nextWindowPos.x + offset, nextWindowPos.y + offset);

    return newPos;
}

} // namespace RavenEngine
