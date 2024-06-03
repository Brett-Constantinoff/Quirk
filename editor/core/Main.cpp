#include <Windows.h>
#include "Editor.hpp"

using namespace Quirk::Editor;

#ifdef _WIN32
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
#else
int main()
#endif
{
    Editor editor;

    editor.tick();
    editor.shutDown();

    return 0;
}
