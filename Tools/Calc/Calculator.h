// Calculator.h
#pragma once
// #include section
// #####################
// Standard includes
#include <string>

// Third-party includes
#include "imgui.h"

// Raven includes

namespace RavenEngine {

enum class Operation {
    None,
    Addition,
    Subtraction,
    Multiplication,
    Division,
    Percent,
    SquareRoot,
    Square,
    Reciprocal
};

class Calculator {
public:
    Calculator();
    void DrawUI();
    void DrawUI(bool& isVisible);
    
private:
    double firstNumber;          
    double secondNumber;       
    double result;               
    double memory{0.0};          // To manage the memory feature
    Operation operation{Operation::None};
    bool userStartedTyping{false};
    std::string previousDisplayText;
    bool equalsPressed{false};
    
    // New members for handling decimal input
    bool isDecimalFirst{false};
    bool isDecimalSecond{false};
    double decimalFactorFirst{1.0};
    double decimalFactorSecond{1.0};

    // UI helper functions
    void DrawButtons(float scale);
    void ButtonPressed(const char* label);
    void DrawResultDisplay(float scale);

    // Operation methods
    void AddDigit(int digit);
    void AddDecimalPoint();
    void Reciprocal();
    void Square();
    void SquareRoot();
    void Percent();
    void ToggleSign();
    void SetOperation(Operation op);
    void Calculate();
    void Clear();
    void Backspace();

    // Utility method
    std::string OperationToString(Operation op);

    static void AspectRatioConstraint(ImGuiSizeCallbackData* data);
    
};

} // namespace RavenEngine
