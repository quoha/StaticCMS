#include "local.hpp"

//============================================================================
// Add(variable)
//
NFTM::Variable *NFTM::SymbolTable::Add(NFTM::Variable *variable) {
	Bucket *b = new Bucket();

	b->variable  = variable;
	b->hashValue = Hash(variable->Name());
    b->prev      = 0;
	b->next      = hash[b->hashValue % hashSize];
    if (b->next) {
        b->next->prev = b;
    }

	hash[b->hashValue % hashSize] = b;

	return variable;
}
