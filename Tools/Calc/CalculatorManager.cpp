// CalculatorManager.cpp

// #include section
// #################
// Standard includes
#include <iostream>

// Third-party includes

// Raven includes
#include "CalculatorManager.h"

namespace RavenEngine {
    CalculatorManager::CalculatorManager() : isCalculatorOpen(false) {}

    void CalculatorManager::Update() {
        calculator.DrawUI(isCalculatorOpen); // Pass visibility status to DrawUI
    }

    void CalculatorManager::ToggleCalculatorVisibility() {
        isCalculatorOpen = !isCalculatorOpen;
        std::cout << "Calculator visibility toggled: " << isCalculatorOpen << std::endl;
    }
}