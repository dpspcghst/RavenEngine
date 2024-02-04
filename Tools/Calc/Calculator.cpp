// #include section
// #####################
// Standard library includes
#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>
#include <regex>
#include <iostream>

// Third-party libraries

// Raven includes
#include "Calculator.h"

namespace RavenEngine {

Calculator::Calculator() 
    : firstNumber(0), secondNumber(0), result(0), operation(Operation::None),
      isDecimalFirst(false), isDecimalSecond(false),
      decimalFactorFirst(1.0), decimalFactorSecond(1.0) {}

static void AspectRatioConstraint(ImGuiSizeCallbackData* data) {
    float aspectRatio = 1.0f; // 1:1 aspect ratio
    data->DesiredSize = ImVec2(data->DesiredSize.x, data->DesiredSize.x / aspectRatio);
}

void Calculator::DrawUI(bool& isVisible) {
    if (!isVisible) {
        return; // Exit if not visible
    }

    ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver); // Set default size
    ImGui::SetNextWindowSizeConstraints(ImVec2(200, 200), ImVec2(FLT_MAX, FLT_MAX), AspectRatioConstraint); // Set the window to have a fixed aspect ratio

    if (!ImGui::Begin("Calculator", &isVisible, ImGuiWindowFlags_NoScrollbar)) {
        ImGui::End();
        return;
    }

    DrawResultDisplay();
    ImGui::Separator();
    DrawNumberButtons();
    DrawOperationButtons();
    DrawMemoryButtons();

    ImGui::End();
}

void Calculator::DrawResultDisplay() {
    std::ostringstream stream;

    auto formatNumber = [](double number) -> std::string {
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(6) << number;
        std::string str = stream.str();
        size_t dot_pos = str.find('.');
        if (dot_pos != std::string::npos) {
            str.erase(str.find_last_not_of('0') + 1, std::string::npos);
            if (str.back() == '.') {
                str.pop_back();
            }
        }
        return str;
    };

    // If the equals button was pressed, show the result.
    if (equalsPressed) {
        stream << formatNumber(result);
    } else {
        // Display the firstNumber
        stream << formatNumber(firstNumber);

        // If an operation is selected, display it next
        if (operation != Operation::None) {
            stream << " " << OperationToString(operation) << " ";
            // If the user has started typing the second number, display the secondNumber
            if (userStartedTyping) {
                stream << formatNumber(secondNumber);
            }
        }
    }

    // Convert the stream into a string for ImGui to display
    std::string displayText = stream.str();

    // Get the window size
    ImVec2 windowSize = ImGui::GetWindowSize();
    // Calculate a font scaling factor based on the window width, adjust this as necessary
    float fontScale = windowSize.x / 160.0f; // example scaling factor, adjust as needed

    // Apply the font scaling
    ImGui::SetWindowFontScale(fontScale);

    // Set the display text to be larger and right-aligned
    ImGui::PushItemWidth(-1); // Push full width
    ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(displayText.c_str()).x);
    ImGui::LabelText("##result", "%s", displayText.c_str());
    ImGui::PopItemWidth();

    // Reset font scale for other UI elements if necessary
    ImGui::SetWindowFontScale(1.0f);

    // Print the display text if it has changed
    if (displayText != previousDisplayText) {
        std::cout << "Display changed: " << displayText << std::endl;
        previousDisplayText = displayText;
    }
}

void Calculator::DrawNumberButtons() {
    // Get the available width for the window and divide by the number of buttons per row
    float windowWidth = ImGui::GetContentRegionAvail().x;
    float buttonWidth = windowWidth / 4 - ImGui::GetStyle().ItemSpacing.x; // Assuming 4 buttons per row
    float buttonHeight = buttonWidth * 0.75f; // Maintain aspect ratio

    // Number buttons
    if (ImGui::Button("7", ImVec2(buttonWidth, buttonHeight))) { AddDigit(7); } ImGui::SameLine();
    if (ImGui::Button("8", ImVec2(buttonWidth, buttonHeight))) { AddDigit(8); } ImGui::SameLine();
    if (ImGui::Button("9", ImVec2(buttonWidth, buttonHeight))) { AddDigit(9); } ImGui::SameLine();
    if (ImGui::Button("x²", ImVec2(buttonWidth, buttonHeight))) { SetOperation(Operation::Square); }

    if (ImGui::Button("4", ImVec2(buttonWidth, buttonHeight))) { AddDigit(4); } ImGui::SameLine();
    if (ImGui::Button("5", ImVec2(buttonWidth, buttonHeight))) { AddDigit(5); } ImGui::SameLine();
    if (ImGui::Button("6", ImVec2(buttonWidth, buttonHeight))) { AddDigit(6); } ImGui::SameLine();
    if (ImGui::Button("√x", ImVec2(buttonWidth, buttonHeight))) { SetOperation(Operation::SquareRoot); }

    if (ImGui::Button("1", ImVec2(buttonWidth, buttonHeight))) { AddDigit(1); } ImGui::SameLine();
    if (ImGui::Button("2", ImVec2(buttonWidth, buttonHeight))) { AddDigit(2); } ImGui::SameLine();
    if (ImGui::Button("3", ImVec2(buttonWidth, buttonHeight))) { AddDigit(3); } ImGui::SameLine();
    if (ImGui::Button("%", ImVec2(buttonWidth, buttonHeight))) { SetOperation(Operation::Percent); }

    if (ImGui::Button("0", ImVec2(buttonWidth, buttonHeight))) { AddDigit(0); } ImGui::SameLine();
    if (ImGui::Button(".", ImVec2(buttonWidth, buttonHeight))) { AddDecimalPoint(); } ImGui::SameLine();
    if (ImGui::Button("1/x", ImVec2(buttonWidth, buttonHeight))) { SetOperation(Operation::Reciprocal); }
}

void Calculator::DrawOperationButtons() {
    // Get the available width for the window and divide by the number of buttons per row
    float windowWidth = ImGui::GetContentRegionAvail().x;
    float buttonWidth = windowWidth / 6 - ImGui::GetStyle().ItemSpacing.x; // Assuming 6 buttons per row
    float buttonHeight = buttonWidth * 0.75f; // Maintain aspect ratio

    // Operation buttons
    if (ImGui::Button("/", ImVec2(buttonWidth, buttonHeight))) { SetOperation(Operation::Division); } ImGui::SameLine();
    if (ImGui::Button("*", ImVec2(buttonWidth, buttonHeight))) { SetOperation(Operation::Multiplication); } ImGui::SameLine();
    if (ImGui::Button("-", ImVec2(buttonWidth, buttonHeight))) { SetOperation(Operation::Subtraction); } ImGui::SameLine();
    if (ImGui::Button("+", ImVec2(buttonWidth, buttonHeight))) { SetOperation(Operation::Addition); } ImGui::SameLine();
    if (ImGui::Button("=", ImVec2(buttonWidth, buttonHeight))) { Calculate(); } ImGui::SameLine();
    // Clear button or other functionalities
    if (ImGui::Button("C", ImVec2(buttonWidth, buttonHeight))) { Clear(); } ImGui::SameLine();
    // Possibly add the +/- toggle button and any other operation buttons you might need
}

void Calculator::DrawMemoryButtons() {
    // Get the available width for the window and divide by the number of buttons per row
    float windowWidth = ImGui::GetContentRegionAvail().x;
    float buttonWidth = windowWidth / 5 - ImGui::GetStyle().ItemSpacing.x; // Assuming 5 buttons per row
    float buttonHeight = buttonWidth * 0.75f; // Maintain aspect ratio

    // Memory buttons
    if (ImGui::Button("MC", ImVec2(buttonWidth, buttonHeight))) { MemoryClear(); } ImGui::SameLine();
    if (ImGui::Button("MR", ImVec2(buttonWidth, buttonHeight))) { MemoryRecall(); } ImGui::SameLine();
    if (ImGui::Button("M+", ImVec2(buttonWidth, buttonHeight))) { MemoryAdd(); } ImGui::SameLine();
    if (ImGui::Button("M-", ImVec2(buttonWidth, buttonHeight))) { MemorySubtract(); } ImGui::SameLine();
    // If you have a memory store button
    if (ImGui::Button("MS", ImVec2(buttonWidth, buttonHeight))) { MemoryStore(); }
}

void Calculator::Calculate() {
    switch (operation) {
        case Operation::Addition:
            result = firstNumber + secondNumber;
            break;
        case Operation::Subtraction:
            result = firstNumber - secondNumber;
            break;
        case Operation::Multiplication:
            result = firstNumber * secondNumber;
            break;
        case Operation::Division:
            result = (secondNumber != 0) ? firstNumber / secondNumber : 0;
            break;
        default:
            break;
    }
    
    firstNumber = result;
    secondNumber = 0;
    operation = Operation::None;
    equalsPressed = true;
    MemoryStore(); // Corrected: No argument is needed
    std::cout << "Result: " << result << std::endl;
}

void Calculator::AddDigit(int digit) {
    if (equalsPressed && operation == Operation::None) {
        Clear();
    }

    if (operation != Operation::None && !equalsPressed) {
        if (isDecimalSecond) {
            secondNumber += digit * decimalFactorSecond;
            decimalFactorSecond /= 10;
        } else {
            secondNumber = secondNumber * 10 + digit;
        }
        userStartedTyping = true;
    } else {
        if (isDecimalFirst) {
            firstNumber += digit * decimalFactorFirst;
            decimalFactorFirst /= 10;
        } else {
            firstNumber = firstNumber * 10 + digit;
        }
    }
}

void Calculator::AddDecimalPoint() {
    if (operation != Operation::None && !equalsPressed) {
        if (!isDecimalSecond) {  // If secondNumber doesn't have a decimal yet
            secondNumber += static_cast<int>(secondNumber) == secondNumber ? 0.0 : 0; // Convert to floating point if it's an integer
            decimalFactorSecond = 0.1; // Next digit will be after the decimal point
            isDecimalSecond = true; // Mark it as decimal
        }
    } else {
        if (!isDecimalFirst) {  // If firstNumber doesn't have a decimal yet
            firstNumber += static_cast<int>(firstNumber) == firstNumber ? 0.0 : 0; // Convert to floating point if it's an integer
            decimalFactorFirst = 0.1; // Next digit will be after the decimal point
            isDecimalFirst = true; // Mark it as decimal
        }
    }
}

void Calculator::SetOperation(Operation op) {
    if (!equalsPressed) {
        if (userStartedTyping && operation != Operation::None) {
            Calculate();
        }
    } else {
        equalsPressed = false;
    }

    operation = op;
    userStartedTyping = false;
    secondNumber = 0;
}

void Calculator::Clear() {
    firstNumber = 0;
    secondNumber = 0;
    result = 0;
    operation = Operation::None;
    equalsPressed = false;
    userStartedTyping = false;
    isDecimalFirst = false;
    decimalFactorFirst = 1.0;
    isDecimalSecond = false;
    decimalFactorSecond = 1.0;
}

void Calculator::MemoryClear() {
    memory = 0.0f;
}

void Calculator::MemoryRecall() {
    // Assuming you want to recall the memory to the firstNumber or result
    if (operation == Operation::None) {
        firstNumber = memory;
        equalsPressed = false;
    } else {
        secondNumber = memory;
    }
}

void Calculator::MemoryAdd() {
    // Adds the result to the memory
    memory += result;
}

void Calculator::MemorySubtract() {
    // Subtracts the result from the memory
    memory -= result;
}

void Calculator::MemoryStore() {
    // Stores the current result into memory
    memory = result;
}

std::string Calculator::OperationToString(Operation op) {
    switch (op) {
        case Operation::Addition: return "+";
        case Operation::Subtraction: return "-";
        case Operation::Multiplication: return "*";
        case Operation::Division: return "/";
        // Add other operations as needed
        default: return "";
    }
}

} // namespace RavenEngine