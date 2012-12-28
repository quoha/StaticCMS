#include "local.hpp"
#include <cstring>

//============================================================================
// StrCopy(str1, str2)
//
char *NFTM::StrCopy(char *s1, const char *s2) {
    if (s1) {
        return std::strcpy(s1, s2 ? s2 : "");
    }
    return s1;
}

//============================================================================
// StrCopy(str1, str2)
//
char *NFTM::StrCopy(char *s1, const char *s2, int maxLength) {
    if (s1) {
        std::strncpy(s1, s2 ? s2 : "", maxLength);
        s1[maxLength] = 0;
    }
    return s1;
}
