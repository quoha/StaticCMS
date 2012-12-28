#include "local.hpp"

//============================================================================
// SymbolTable(void)
//
NFTM::SymbolTable::SymbolTable(void) {
	for (int idx = 0; idx < hashSize; idx++) {
		hash[idx] = 0;
	}
}
