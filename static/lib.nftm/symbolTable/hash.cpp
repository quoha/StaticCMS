#include "../local.hpp"

//============================================================================
// Hash(text)
//
unsigned int NFTM::SymbolTable::Hash(const char *str) const {
	unsigned int djbHash = 0;

	while (*str) {
		djbHash  = (djbHash *       33) + (*str);

		str++;
	}

	return djbHash;
}
