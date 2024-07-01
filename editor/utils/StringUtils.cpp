#include "StringUtils.hpp"

#include <cassert>
#include <string>

namespace Quirk::Editor::Utils::StringUtils
{
    uint32_t Stricmp(const char* s1, const char* s2)
    {
        uint32_t d;
        while ((d = std::toupper(*s2) - std::toupper(*s1)) == 0 && *s1)
        {
            s1++;
            s2++;
        }
        return d;
    }

    uint32_t Strnicmp(const char* s1, const char* s2, uint32_t n)
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

    char* Strdup(const char* s)
    {
        assert(s);
        size_t len = strlen(s) + 1;
        void* buf = new char[](len);
        assert(buf);
        return static_cast<char*>(memcpy(buf, (const void*)s, len));
    }

    void Strtrim(char* s)
    {
        char* str_end = s + strlen(s);
        while (str_end > s && str_end[-1] == ' ') str_end--;
        *str_end = 0;
    }
}
