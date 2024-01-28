// CalculatorManager.h
#ifndef CALCULATOR_MANAGER_H
#define CALCULATOR_MANAGER_H

#include "Calculator.h"

namespace RavenEngine {
    class CalculatorManager {
    public:
        CalculatorManager();
        void Update();
        void ToggleCalculatorVisibility();

    private:
        Calculator calculator;
        bool isCalculatorOpen;
    };
}
#endif // CALCULATOR_MANAGER_H