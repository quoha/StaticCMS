#include "local.hpp"

//============================================================================
// Dump()
//
void NFTM::SymbolTable::Dump(NFTM::OutputStream *os) const {
	os->Write(" dump:\tSymbolTable ----------------------------------------------\n");
	for (int idx = 0; idx < hashSize; idx++) {
		Bucket *b = hash[idx];
		for (int idy = 0; b; idy++, b = b->next) {
			if (idy == 0) {
				os->Write("%5d:\t%08x %-10s %s\n", idx, b->hashValue, b->word->Kind(), b->word->Name());
			} else {
				os->Write("\t%08x %-10s %s\n", b->hashValue, b->word->Kind(), b->word->Name());
			}
		}
	}

	os->Write(" dump:\t----------------------------------------------------------\n");
}
