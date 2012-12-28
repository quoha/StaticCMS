#include "local.hpp"
#include <cstring>

//============================================================================
// StrCat(str1, str2)
//
char *NFTM::StrCat(const char *str1, const char *str2) {
	return StrCat(str1, str2, 0, 0);
}

//============================================================================
// StrCat(str1, str2, str3)
//
char *NFTM::StrCat(const char *str1, const char *str2, const char *str3) {
	return StrCat(str1, str2, str3, 0);
}

//============================================================================
// StrCat(str1, str2, str3, str4)
//
char *NFTM::StrCat(const char *str1, const char *str2, const char *str3, const char *str4) {
	str1 = str1 ? str1 : "";
	str2 = str2 ? str2 : "";
	str3 = str3 ? str3 : "";
	str4 = str4 ? str4 : "";


	char *str = new char[std::strlen(str1) + std::strlen(str2) + std::strlen(str3) + std::strlen(str4) + 1];

	*str = 0;

	std::strcat(str, str1);
	std::strcat(str, str2);
	std::strcat(str, str3);
	std::strcat(str, str4);

	return str;
}
