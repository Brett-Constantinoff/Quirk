#include "LogPanel.hpp"

#include <spdlog/spdlog.h>

Quirk::Editor::Components::LogPanel::LogPanel(const char* title) : m_title(title), m_autoScroll(true)
{
    Clear();    
}

void Quirk::Editor::Components::LogPanel::Clear()
{
    m_buf.clear();
    m_lineOffsets.clear();
    m_lineOffsets.push_back(0);
}

// Adds a log entry to the buffer
// The log entry is formatted according to the given format string and arguments
void Quirk::Editor::Components::LogPanel::AddLog(const char* fmt, ...)
{
    uint32_t oldSize = m_buf.size();
    va_list args;
    va_start(args, fmt);
    m_buf.appendfv(fmt, args);
    va_end(args);
    for (uint32_t newSize = m_buf.size(); oldSize < newSize; oldSize++)
    {
        if (m_buf[oldSize] == '\n')
            m_lineOffsets.push_back(oldSize + 1);
    }
}

void Quirk::Editor::Components::LogPanel::Draw(const char* title, bool* p_open)
{
    if (!ImGui::Begin(title, p_open))
    {
        ImGui::End();
        spdlog::error("LogPanel::Draw: ImGui::Begin failed");
        return;
    }

    DrawOptions();
    DrawMainWindow();
    ImGui::End();
}

void Quirk::Editor::Components::LogPanel::DrawOptions()
{
    if (ImGui::BeginPopup("Options"))
    {
        ImGui::Checkbox("Auto-scroll", &m_autoScroll);
        ImGui::EndPopup();
    }

    if (ImGui::Button("Options"))
        ImGui::OpenPopup("Options");
    ImGui::SameLine();
    bool clear = ImGui::Button("Clear");
    ImGui::SameLine();
    bool copy = ImGui::Button("Copy");
    ImGui::SameLine();
    m_filter.Draw("Filter", -100.0f);

    ImGui::Separator();

    if (clear) Clear();
    if (copy) ImGui::LogToClipboard();
}

void Quirk::Editor::Components::LogPanel::DrawMainWindow()
{
    if (ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar))
    {
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        if (m_filter.IsActive())
        {
            DrawFilteredLog();
        }
        else
        {
            DrawUnfilteredLog();
        }
        ImGui::PopStyleVar();

        if (m_autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);

        ImGui::EndChild();
    }
}

void Quirk::Editor::Components::LogPanel::DrawFilteredLog()
{
    const char* buf = m_buf.begin();
    const char* buf_end = m_buf.end();
    for (int line_no = 0; line_no < m_lineOffsets.size(); line_no++)
    {
        const char* line_start = buf + m_lineOffsets[line_no];
        const char* line_end = (line_no + 1 < m_lineOffsets.size()) ? (buf + m_lineOffsets[line_no + 1] - 1) : buf_end;
        if (m_filter.PassFilter(line_start, line_end))
            ImGui::TextUnformatted(line_start, line_end);
    }
}

void Quirk::Editor::Components::LogPanel::DrawUnfilteredLog()
{
    const char* buf = m_buf.begin();
    const char* buf_end = m_buf.end();
    ImGuiListClipper clipper;
    clipper.Begin(m_lineOffsets.size());
    while (clipper.Step())
    {
        for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
        {
            const char* line_start = buf + m_lineOffsets[line_no];
            const char* line_end = (line_no + 1 < m_lineOffsets.size()) ? (buf + m_lineOffsets[line_no + 1] - 1) : buf_end;
            ImGui::TextUnformatted(line_start, line_end);
        }
    }
    clipper.End();
}

void Quirk::Editor::Components::LogPanel::render()
{
    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin("Quirk Engine: Log");
    ImGui::End();
    Draw("Quirk Engine: Log", nullptr);
}
