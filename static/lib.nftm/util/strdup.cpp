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
