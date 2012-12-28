#include "local.hpp"
#include <cstring>

//============================================================================
// Lookup(const char *name)
//    searchs the table for an item with the name. note that if there
//    are multiple items with the same name, only the first one found
//    will be returned.
//
// RETURN
//    NULL      no item found
//    not-NULL  the address of the first item with the same name
//
NFTM::Variable *NFTM::SymbolTable::Lookup(const char *name) const {
	unsigned int hashValue = Hash(name);

	Bucket *b = hash[hashValue % hashSize];

	while (b) {
		if (b->hashValue == hashValue) {
			if (std::strcmp(name, b->variable->Name()) == 0) {
				return b->variable;
			}
		}

		b = b->next;
	}

	return 0;
}
