#include "local.hpp"
#include <cstring>

//============================================================================
// StrDup(str)
//
char *NFTM::StrDup(const char *str) {
    int   len = (int)std::strlen(str ? str : "");
    char *dst = new char[len + 1];

    std::strcpy(dst, str ? str : "");

	return dst;
}

//============================================================================
// StrDup(str, length)
//
char *NFTM::StrDup(const char *str, int length) {
    int len = (int)std::strlen(str ? str : "");

    if (len < 0) {
        length = len;
    } else if (len < length) {
        length = len;
    }

    char *dst = new char[length + 1];

    std::strncpy(dst, str ? str : "", length);
    dst[length] = 0;

	return dst;
}
