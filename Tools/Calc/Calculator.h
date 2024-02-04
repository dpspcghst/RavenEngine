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
    void DrawNumberButtons();
    void DrawOperationButtons();
    void DrawMemoryButtons();
    void DrawResultDisplay();

    // Operation methods
    void AddDigit(int digit);
    void AddDecimalPoint();
    void SetOperation(Operation op);
    void Calculate();
    void Clear();

    // Memory methods
    void MemoryClear();
    void MemoryRecall();
    void MemoryAdd();
    void MemorySubtract();
    void MemoryStore();

    // Utility method
    std::string OperationToString(Operation op);
};

} // namespace RavenEngine
