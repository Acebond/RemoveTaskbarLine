#include <Windows.h>
#include <iostream>

int main() {

    HWND hWnd = FindWindowEx(nullptr, nullptr, L"Shell_TrayWnd", nullptr);
    if (hWnd == NULL) {
        std::cout << "FindWindowEx() failed to retrieve a handle to the Shell_TrayWnd.\n";
        return 1;
    }

    RECT TaskbarRect;
    if (GetWindowRect(hWnd, &TaskbarRect) == ERROR) {
        std::cout << "GetWindowRect() failed to retrieve the dimensions of the bounding rectangle of the specified window.\n";
        return 1;
    }

    double ScaleFactor = GetDpiForWindow(hWnd) / 96.00;

    
    const int taskbarTop = 1; // Remove the top 1px border
    const int taskbarLeft = 0;
    const int taskbarWidth = (TaskbarRect.right - TaskbarRect.left) * ScaleFactor;
    const int taskbarHeight = (TaskbarRect.bottom - TaskbarRect.top) * ScaleFactor;
    
    HRGN hRgn = CreateRectRgn(taskbarLeft, taskbarTop, taskbarWidth, taskbarHeight);
    if (hRgn == NULL) {
        std::cout << "CreateRectRgn() failed to create a rectangular region.\n";
        return 1;
    }

    if (SetWindowRgn(hWnd, hRgn, true) == ERROR) {
        std::cout << "SetWindowRgn() failed to set the window region of Shell_TrayWnd.\n";
    }

    DeleteObject(hRgn);
    return 0;
}
