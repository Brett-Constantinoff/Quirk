#pragma once
#include <vector>

#include "../Component.hpp"


namespace Quirk::Editor::Components
{
    class ConsolePanel : public Component
    {
    public:
        ConsolePanel(const char* title);
        ~ConsolePanel() override;

        void render() override;

    private:
        void ClearLog();
        void AddLog(const char* fmt, ...);
        void Draw(const char* title, bool* p_open = nullptr);
        void DrawOptions();
        void DrawMainWindow();
        void ExecCommand(const char* command_line);
        void PrintWelcomeMessage();
        int32_t TextEditCallback(ImGuiInputTextCallbackData* data);
        static int32_t TextEditCallbackStub(ImGuiInputTextCallbackData* data);
        

    private:
        char m_InputBuf[256]; // Text input buffer
        std::vector<char*> m_Items; 
        std::vector<const char*> m_Commands; // Command history
        std::vector<char*> m_History; // History as a string
        int32_t m_HistoryPos; // -1: new line, 0..History.Size-1 browsing history.
        ImGuiTextFilter m_Filter; // Filter to only display commands with a specific filter
        bool m_AutoScroll; 
        bool m_ScrollToBottom; 
    };
}
