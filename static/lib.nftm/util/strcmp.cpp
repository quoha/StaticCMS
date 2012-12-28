#include "local.hpp"
#include <cstring>

//============================================================================
// StrCmp(s1, s2)
//
bool NFTM::StrCmp(const char *s1, const char *s2) {
	if (s1 == s2) {
		return true;
	}
	if (s1 && s2 && std::strcmp(s1, s2) == 0) {
		return true;
	}
	return false;
}
