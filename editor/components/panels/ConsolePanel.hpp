#pragma once
#include <vector>

#include "../Component.hpp"

namespace Quirk::Editor::Components
{
    class ConsolePanel : public Component
    {
    public:
        ConsolePanel(const char* title);
        ~ConsolePanel() override = default;

        void render() override;

        //TODO: move these to a string helpers class
        uint32_t Stricmp(const char* s1, const char* s2);
        uint32_t Strnicmp(const char* s1, const char* s2, uint32_t n);
        char* Strdup(const char* s);
        void Strtrim(char* s);

    private:
        void ClearLog();
        void AddLog(const char* fmt, ...);
        void Draw(const char* title, bool* p_open = nullptr);
        void DrawOptions();
        void DrawMainWindow();
        void ExecCommand(const char* command_line);
        void PrintWelcomeMessage();
        uint32_t TextEditCallback(ImGuiInputTextCallbackData* data);
        static int32_t TextEditCallbackStub(ImGuiInputTextCallbackData* data);
        

    private:
        std::string m_title;
        char m_InputBuf[256]; // Text input buffer
        std::vector<char*> m_Items; 
        std::vector<const char*> m_Commands; // Command history
        std::vector<char*> m_History; // History as a string
        int m_HistoryPos; // -1: new line, 0..History.Size-1 browsing history.
        ImGuiTextFilter m_Filter; // Filter to only display commands with a specific filter
        bool m_AutoScroll; 
        bool m_ScrollToBottom; 
    };
}
