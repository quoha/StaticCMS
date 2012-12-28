#include "local.hpp"

//============================================================================
// Dump()
//
void NFTM::SymbolTable::Dump(NFTM::OutputStream *os, bool showHash, bool showVar) const {
	os->Write(" dump:\tSymbolTable ----------------------------------------------\n");
	for (int idx = 0; idx < hashSize; idx++) {
		Bucket *b = hash[idx];
		for (int idy = 0; b; idy++, b = b->next) {
			if (idy == 0) {
				os->Write("%5d:\t-----------\n", idx);
			}
            if (!showHash && !showVar) {
                os->Write("\tvar %s\n", b->variable->Name());
            }
            if (showHash) {
                if (showVar) {
                    os->Write("\thash value %16x\n", b->hashValue);
                } else {
                    os->Write("\thash value %16x %s\n", b->hashValue, b->variable->Name());
                }
            }
            if (showVar) {
                b->variable->Dump(os);
            }
		}
	}

	os->Write(" dump:\t----------------------------------------------------------\n");
}
