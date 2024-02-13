// filedialog.cpp

// #include section
// #####################
// Standard library includes
#include <Windows.h>
#include <commdlg.h>

#include <locale>
#include <codecvt>

// Third-party library includes
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

// Raven includes
#include "FileDialog.h"

namespace RavenEngine {

std::string FileDialog::OpenFileDialog(GLFWwindow* ownerWindow, const std::wstring& filter) {
    OPENFILENAMEW ofn;
    WCHAR szFile[260] = {0};
    HWND hwnd = glfwGetWin32Window(ownerWindow);

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAMEW);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile) / sizeof(WCHAR);
    ofn.lpstrFilter = filter.c_str();
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameW(&ofn) == TRUE) {
        int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, szFile, -1, NULL, 0, NULL, NULL);
        std::string filePath(sizeNeeded, 0);
        WideCharToMultiByte(CP_UTF8, 0, szFile, -1, &filePath[0], sizeNeeded, NULL, NULL);
        filePath.resize(sizeNeeded - 1); // Remove extra null terminator
        return filePath;
    }
    return "";
}

} // namespace RavenEngine