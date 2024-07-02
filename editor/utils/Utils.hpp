#pragma once

#include <windows.h>
#include <iostream>

namespace Quirk::Editor::Uitls
{
    static void createConsole()
    {
        AllocConsole();

        FILE* fp;
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);
        freopen_s(&fp, "CONIN$", "r", stdin);

        std::cout.clear();
        std::cerr.clear();
        std::cin.clear();

        std::ios::sync_with_stdio();

        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        HANDLE hStderr = GetStdHandle(STD_ERROR_HANDLE);
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

        std::wcout.clear();
        std::wcin.clear();
        std::wcerr.clear();
        std::wclog.clear();
    }
} // namespace Quirk::Editor::Uitls