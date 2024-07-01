#include "StringUtils.hpp"
#include <locale>
#include "imgui.h"

uint32_t Quirk::Editor::Uitls::StringUtils::Stricmp(const char* s1, const char* s2)
{
    uint32_t d;
    while ((d = std::toupper(*s2) - std::toupper(*s1)) == 0 && *s1)
    {
        s1++;
        s2++;
    }
    return d;
}

uint32_t Quirk::Editor::Uitls::StringUtils::Strnicmp(const char* s1, const char* s2, uint32_t n)
{
    uint32_t d = 0;
    while (n > 0 && (d = std::toupper(*s2) - std::toupper(*s1)) == 0 && *s1)
    {
        s1++;
        s2++;
        n--;
    }
    return d;
}

char* Quirk::Editor::Uitls::StringUtils::Strdup(const char* s)
{
    IM_ASSERT(s);
    size_t len = strlen(s) + 1;
    void* buf = ImGui::MemAlloc(len);
    IM_ASSERT(buf);
    return (char*)memcpy(buf, (const void*)s, len);
}

void Quirk::Editor::Uitls::StringUtils::Strtrim(char* s)
{
    char* str_end = s + strlen(s);
    while (str_end > s && str_end[-1] == ' ') str_end--;
    *str_end = 0;
}
