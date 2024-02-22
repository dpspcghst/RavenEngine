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

void Calculator::DrawUI(bool& isVisible) {
    if (!isVisible) return; // Exit if not visible

    // Remove ImGuiWindowFlags_AlwaysAutoResize to allow manual resizing
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

    if (!ImGui::Begin("Calculator", &isVisible, window_flags)) {
        ImGui::End();
        return;
    }

    // Calculate the scale based on the current window size
    ImVec2 windowSize = ImGui::GetContentRegionAvail();
    float scale = std::min(windowSize.x / 300.0f, windowSize.y / 500.0f);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4.0f * scale, 4.0f * scale));

    DrawResultDisplay(scale);
    ImGui::Separator();
    DrawButtons(scale);

    // Optional: Add a spacer to adjust for unused space or to maintain layout
    // ImGui::Dummy(ImVec2(0.0f, ...));

    ImGui::PopStyleVar();
    ImGui::End();
}

void Calculator::AspectRatioConstraint(ImGuiSizeCallbackData* data) {
    float aspectRatio = 3.0f / 5.0f; // Desired aspect ratio: 3:5
    // Calculate the height based on the current width and desired aspect ratio
    float desiredHeight = data->CurrentSize.x / aspectRatio;
    // Set the desired size maintaining the aspect ratio
    data->DesiredSize = ImVec2(data->CurrentSize.x, desiredHeight);
}

void Calculator::DrawResultDisplay(float scale) {
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

void Calculator::DrawButtons(float scale) {
    // Calculate button dimensions based on the window size and scale
    float buttonWidth = ImGui::GetContentRegionAvail().x / 4 - ImGui::GetStyle().ItemSpacing.x;
    float buttonHeight = buttonWidth * 0.75f;

    // Define button labels in the order they should appear, reflecting the 4x6 layout
    const char* buttons[24] = {
        "%", "CE", "C", "<-",
        "1/x", "x²", "√x", "/",
        "7", "8", "9", "*",
        "4", "5", "6", "-",
        "1", "2", "3", "+",
        "+/-", "0", ".", "="
    };

    // Iterate through the buttons and create them dynamically
    for (int i = 0; i < 24; ++i) {
        if (i % 4 != 0) ImGui::SameLine();
        if (ImGui::Button(buttons[i], ImVec2(buttonWidth, buttonHeight))) {
            ButtonPressed(buttons[i]);
        }
    }
}

void Calculator::ButtonPressed(const char* label) {
    if (std::isdigit(label[0]) || (label[0] == '.' && std::strlen(label) == 1)) { // Check if digit or decimal point
        if (label[0] == '.') {
            AddDecimalPoint();
        } else {
            int digit = label[0] - '0';
            AddDigit(digit);
        }
    } else {
        // Map label to an action or operation
        if (strcmp(label, "+") == 0) {
            SetOperation(Operation::Addition);
        } else if (strcmp(label, "-") == 0) {
            SetOperation(Operation::Subtraction);
        } else if (strcmp(label, "*") == 0) {
            SetOperation(Operation::Multiplication);
        } else if (strcmp(label, "/") == 0) {
            SetOperation(Operation::Division);
        } else if (strcmp(label, "=") == 0) {
            Calculate();
        } else if (strcmp(label, "C") == 0) {
            Clear();
        } else if (strcmp(label, "CE") == 0) {
            Clear(); // Assuming CE behaves like C for simplicity
        } else if (strcmp(label, "<-") == 0) {
            Backspace();
        } else if (strcmp(label, "1/x") == 0) {
            Reciprocal();
        } else if (strcmp(label, "x²") == 0) {
            Square();
        } else if (strcmp(label, "√x") == 0) {
            SquareRoot();
        } else if (strcmp(label, "%") == 0) {
            Percent();
        } else if (strcmp(label, "+/-") == 0) {
            ToggleSign();
        }
    }
}

// #####################
// #####################
// #####################

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

void Calculator::Backspace() {
    if (operation != Operation::None && userStartedTyping) {
        // Convert the second number to a string
        std::string numberStr = std::to_string(secondNumber);

        // Remove the last character
        numberStr.pop_back();

        // Convert the string back to a number
        secondNumber = std::stod(numberStr);
    } else {
        // Convert the first number to a string
        std::string numberStr = std::to_string(firstNumber);

        // Remove the last character
        numberStr.pop_back();

        // Convert the string back to a number
        firstNumber = std::stod(numberStr);
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

void Calculator::Reciprocal() {
    // Perform 1/x operation
    if (operation == Operation::None) {
        firstNumber = (firstNumber != 0) ? 1 / firstNumber : 0;
    } else {
        secondNumber = (secondNumber != 0) ? 1 / secondNumber : 0;
    }
    equalsPressed = true;
}

void Calculator::Square() {
    // Perform x² operation
    if (operation == Operation::None) {
        firstNumber *= firstNumber;
    } else {
        secondNumber *= secondNumber;
    }
    equalsPressed = true;
}

void Calculator::SquareRoot() {
    // Perform √x operation
    if (operation == Operation::None) {
        firstNumber = std::sqrt(firstNumber);
    } else {
        secondNumber = std::sqrt(secondNumber);
    }
    equalsPressed = true;
}

void Calculator::Percent() {
    // Implement percent logic here, if applicable
}

void Calculator::ToggleSign() {
    // Toggle the sign of the currently active number
    if (operation == Operation::None || !userStartedTyping) {
        firstNumber = -firstNumber;
    } else {
        secondNumber = -secondNumber;
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