#include <Windows.h>
#include "Editor.hpp"

using namespace Quirk::Editor;

#ifdef _WIN32

#include "../utils/Utils.hpp"

using namespace Quirk::Editor::Uitls;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // create a console for logging if were a windows application
    createConsole();
#else
int main()
{
#endif
    Editor editor;

    editor.tick();
    editor.shutDown();

    return 0;
}
