#include "ConsolePanel.hpp"

#include <spdlog/spdlog.h>

#include "imgui_internal.h"
#include "../../utils/StringUtils.hpp"

namespace Quirk::Editor::Components
{
    ConsolePanel::ConsolePanel(const char* title) : Component(title)
    {
        m_ScrollToBottom = false;
        m_AutoScroll = true;
        m_HistoryPos = -1;
        memset(m_InputBuf, 0, sizeof(m_InputBuf));
        m_Commands = { "HELP", "HISTORY", "CLEAR", "CLASS", "EXIT" };
        ClearLog();
        PrintWelcomeMessage();
    }
    
    ConsolePanel::~ConsolePanel()
    {
        ClearLog();
    }
    
    void ConsolePanel::ClearLog()
    {
        for(auto item: m_Items)
        {
            ImGui::MemFree(item);
        }
        m_Items.clear();
    }
    
    void ConsolePanel::AddLog(const char* fmt, ...)
    {
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        int32_t buf_size = vsnprintf(buf, sizeof(buf), fmt, args);
        va_end(args);
    
        if(buf_size < 0)
        {
            //TODO: Handle encoding error
            spdlog::error("ConsolePanel::AddLog: Encoding error");
        }
    
        if(buf_size >= IM_ARRAYSIZE(buf))
        {
            //TODO: Handle truncation error
            spdlog::error("ConsolePanel::AddLog: Truncated log message: %.*s...", IM_ARRAYSIZE(buf) - 1, buf);
        }
    
        char* allocated_memory = static_cast<char*>(ImGui::MemAlloc(strlen(buf) + 1));
        if (allocated_memory != nullptr)
        {
            strcpy_s(allocated_memory, strlen(buf)+1, buf);
            m_Items.push_back(allocated_memory);
        }
        else
        {
            //TODO: Handle allocation failure if needed
            spdlog::error("ConsolePanel::AddLog: Failed to allocate memory for log message");
        }
    }
    
    void ConsolePanel::Draw(const char* title, bool* p_open)
    {
        ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
        if (!ImGui::Begin(title, p_open))
        {
            ImGui::End();
            return;
        }
    
        DrawOptions();
        DrawMainWindow();
        ImGui::End();
    }
    
    void ConsolePanel::DrawOptions()
    {
        if (ImGui::BeginPopup("Options"))
        {
            ImGui::Checkbox("Auto-scroll", &m_AutoScroll);
            ImGui::EndPopup();
        }
    
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");
        ImGui::SameLine();
        bool clear = ImGui::SmallButton("Clear");
        ImGui::SameLine();
        bool copy_to_clipboard = ImGui::SmallButton("Copy");
    
        ImGui::Separator();
    
        if (clear) ClearLog();
        if (copy_to_clipboard) ImGui::LogToClipboard();
    }
    
    void ConsolePanel::DrawMainWindow()
    {
        const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
            if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), ImGuiChildFlags_None,
                                  ImGuiWindowFlags_HorizontalScrollbar))
            {
                if (ImGui::BeginPopupContextWindow())
                {
                    if (ImGui::Selectable("Clear")) ClearLog();
                    ImGui::EndPopup();
                }
    
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));
    
                if (m_Filter.IsActive())
                {
                    for (auto item : m_Items)
                    {
                        if (!m_Filter.PassFilter(item))
                            continue;
                        ImGui::TextUnformatted(item);
                    }
                }
                else
                {
                    for (auto item : m_Items)
                        ImGui::TextUnformatted(item);
                }
    
                if (m_ScrollToBottom || (m_AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
                    ImGui::SetScrollHereY(1.0f);
                m_ScrollToBottom = false;
    
                ImGui::PopStyleVar();
                ImGui::EndChild();
            }
    
            ImGui::Separator();
    
            bool reclaim_focus = false;
            ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue |
                                                   ImGuiInputTextFlags_EscapeClearsAll |
                                                   ImGuiInputTextFlags_CallbackCompletion |
                                                   ImGuiInputTextFlags_CallbackHistory;
            if (ImGui::InputText("Input", m_InputBuf, sizeof(m_InputBuf), input_text_flags, &TextEditCallbackStub, (void*)this))
            {
                const char* s = m_InputBuf;
                while (*s == ' ') ++s;
                if (*s)
                    ExecCommand(s);
                strcpy_s(m_InputBuf, sizeof(m_InputBuf), "");
                reclaim_focus = true;
            }
    
            ImGui::SetItemDefaultFocus();
            if (reclaim_focus)
                ImGui::SetKeyboardFocusHere(-1);
    }
    
    void ConsolePanel::ExecCommand(const char* command_line)
    {
        AddLog("# %s\n", command_line);
    
        m_HistoryPos = -1;
        for (auto it = m_History.begin(); it != m_History.end(); ++it)
        {
            if (Utils::StringUtils::Stricmp(*it, command_line) == 0)
            {
                ImGui::MemFree(*it);
                m_History.erase(it);
                break;
            }
        }
        m_History.push_back(ImStrdup(command_line));
    
        if (Utils::StringUtils::Stricmp(command_line, "CLEAR") == 0)
        {
            ClearLog();
        }
        else if (Utils::StringUtils::Stricmp(command_line, "HELP") == 0)
        {
            AddLog("Commands:");
            for (const char* cmd : m_Commands)
                AddLog("- %s", cmd);
        }
        else if (Utils::StringUtils::Stricmp(command_line, "HISTORY") == 0)
        {
            uint64_t first = m_History.size() - 10;
            for (uint64_t i = first > 0 ? first : 0; i < m_History.size(); ++i)
                AddLog("%3d: %s\n", i, m_History[i]);
        }
        else
        {
            AddLog("Unknown command: '%s'\n", command_line);
        }
    
        m_ScrollToBottom = true;
    }
    
    void ConsolePanel::PrintWelcomeMessage()
    {
        AddLog("                           \t          ___\n"
                        "                           \t         /\\  \\\n"
                        "   ___        _      _    \t         /  \\/ \\\n"
                        "  / _ \\ _   _(_)_ __| | __\t    ___  \\   O /  ___\n"
                        " | | | | | | | | '__| |/ /\t   /    \\ \\   / /    \\\n"
                        " | |_| | |_| | | |  |   < \t  /   __ -    -  __   \\\n"
                        "  \\__\\_\\\\__,_|_|_|  |_|\\_\\\t /___/ | <>   <> | \\___\\\n"
                        "                          \t O  ___|    ^    |___  O\n"
                        "  ___           _          \t /     \\  -^-  /    \\\n"
                        " | __|_ _  __ _(_)_ _  ___ \t/   /\\  \\_____/ /\\   \\\n"
                        " | _|| ' \\/ _` | | ' \\/ -_)\t\\_ / /          \\ \\_ /\n"
                        " |___|_||_\\__, |_|_||_\\___|\tO   /   /\\   /\\  \\  O\n"
                        "          |___/            \t     \\ /  \\ /  \\ /\n"
                        "                           \t      O    O    O\n");
    
    
        AddLog("Welcome to Quirk Engine!  Type 'HELP' for help.\n");
    }
    
    int32_t ConsolePanel::TextEditCallback(ImGuiInputTextCallbackData* data)
    {
        switch (data->EventFlag)
            {
            case ImGuiInputTextFlags_CallbackCompletion:
            {
                const char* word_end = data->Buf + data->CursorPos;
                const char* word_start = word_end;
                while (word_start > data->Buf)
                {
                    if (const char c = word_start[-1]; c == ' ' || c == '\t' || c == ',' || c == ';')
                        break;
                    word_start--;
                }
    
                std::vector<const char*> candidates;
                for (auto cmd : m_Commands)
                    if (Utils::StringUtils::Strnicmp(cmd, word_start, static_cast<uint32_t>(word_end - word_start)) == 0)
                        candidates.push_back(cmd);
    
                if (candidates.empty())
                {
                    AddLog("No match for \"%.*s\"!\n", static_cast<uint32_t>(word_end - word_start), word_start);
                }
                else if (candidates.size() == 1)
                {
                    data->DeleteChars(static_cast<int32_t>(word_start - data->Buf), static_cast<int32_t>(word_end - word_start));
                    data->InsertChars(data->CursorPos, candidates[0]);
                    data->InsertChars(data->CursorPos, " ");
                }
                else
                {
                    uint32_t match_len = static_cast<uint32_t>(word_end - word_start);
                    for (;;)
                    {
                        int32_t c = 0;
                        bool all_candidates_matches = true;
                        for (uint32_t i = 0; i < candidates.size() && all_candidates_matches; i++)
                            if (i == 0)
                                c = toupper(candidates[i][match_len]);
                            else if (c == 0 || c != toupper(candidates[i][match_len]))
                                all_candidates_matches = false;
                        if (!all_candidates_matches)
                            break;
                        match_len++;
                    }
    
                    if (match_len > 0)
                    {
                        data->DeleteChars(static_cast<int32_t>(word_start - data->Buf), static_cast<int32_t>(word_end - word_start));
                        data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
                    }
    
                    AddLog("Possible matches:\n");
                    for (const char* candidate : candidates)
                        AddLog("- %s\n", candidate);
                }
                break;
            }
            case ImGuiInputTextFlags_CallbackHistory:
            {
                const int32_t prev_history_pos = m_HistoryPos;
                if (data->EventKey == ImGuiKey_UpArrow)
                {
                    if (m_HistoryPos == -1)
                        m_HistoryPos = static_cast<int32_t>(m_History.size() - 1);
                    else if (m_HistoryPos > 0)
                        m_HistoryPos--;
                }
                else if (data->EventKey == ImGuiKey_DownArrow)
                {
                    if (m_HistoryPos != -1)
                        if (++m_HistoryPos >= static_cast<int32_t>(m_History.size()))
                            m_HistoryPos = -1;
                }
    
                if (prev_history_pos != m_HistoryPos)
                {
                    const char* history_str = (m_HistoryPos >= 0) ? m_History[m_HistoryPos] : "";
                    data->DeleteChars(0, data->BufTextLen);
                    data->InsertChars(0, history_str);
                }
                    break;
            }
            default: return 0;
            
            }
            return 0;
    }
    
    int32_t ConsolePanel::TextEditCallbackStub(ImGuiInputTextCallbackData* data)
    {
        ConsolePanel* console = static_cast<ConsolePanel*>(data->UserData);
        return console->TextEditCallback(data);
    }
    
    void ConsolePanel::render()
    {
       Draw(m_title, nullptr);
    }
}


