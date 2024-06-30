#pragma once
#include "../Component.hpp"
#include <vector>
#include <string>

namespace Quirk::Editor::Components
{
  class LogPanel : public Component
  {
  public:
    LogPanel(const char* title);
    ~LogPanel() override = default;

    void render() override;

  private:
    void Clear();
    void AddLog(const char* fmt, ...);
    void Draw(const char* title, bool* p_open = nullptr);
    void DrawOptions();
    void DrawMainWindow();
    void DrawFilteredLog();
    void DrawUnfilteredLog();

    std::string m_title;
    ImGuiTextBuffer m_buf;
    ImGuiTextFilter m_filter;
    std::vector<int> m_lineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool m_autoScroll; // Keep scrolling if already at the bottom.
  };  
}

