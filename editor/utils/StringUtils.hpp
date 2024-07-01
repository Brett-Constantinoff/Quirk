#pragma once
#include <cstdint>

namespace Quirk::Editor::Utils::StringUtils
{
    // Compare two strings ignoring case  
    uint32_t Stricmp(const char* s1, const char* s2);  
    // Compare two strings ignoring case up to n characters  
    uint32_t Strnicmp(const char* s1, const char* s2, uint32_t n);  
    // Duplicate a string  
    char* Strdup(const char* s);  
    // Trim a string void Strtrim(char* s);
}
