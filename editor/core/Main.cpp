#ifdef _WIN32
#include <Windows.h>
#endif

#include "../utils/Utils.hpp"
#include "Editor.hpp"

using namespace Quirk::Editor::Uitls;
using namespace Quirk::Editor;

#ifdef _WIN32
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    createConsole();
#else
int main()
{
#endif
    Editor::init();
    Editor::run();
    Editor::shutdown();
} 
