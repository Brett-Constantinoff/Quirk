#pragma once
#include <cstdint>

namespace Quirk::Editor::Uitls
{
   class StringUtils
   {
   public:
      // Compare two strings ignoring case
      static uint32_t Stricmp(const char* s1, const char* s2);
      // Compare two strings ignoring case up to n characters
      static uint32_t Strnicmp(const char* s1, const char* s2, uint32_t n);
      // Duplicate a string
      static char* Strdup(const char* s);
      // Trim a string 
      static void Strtrim(char* s);
   }; 
}

