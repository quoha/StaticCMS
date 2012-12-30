#include "local.hpp"

//============================================================================
// ~SymbolTable()
//
NFTM::SymbolTable::~SymbolTable() {
	for (int idx = 0; idx < hashSize; idx++) {
		Bucket *b = hash[idx];
		while (b) {
			Bucket *tmp = b->next;
			delete b;
			b = tmp;
		}
	}
    delete errorLog;
}
