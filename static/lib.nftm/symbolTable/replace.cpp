#include "local.hpp"
#include <cstring>

//============================================================================
// Replace(word)
//   replaces the first item with the same name in the table.
//   if there are no items with the same name, then the word is inserted.
//
// RETURN
//   true   an item was replaced
//   false  the word was added but no item was replaced
//
bool NFTM::SymbolTable::Replace(NFTM::Word *word) {

    // find any existing item
    //
    const char *name = word->Name();
	unsigned int hashValue = Hash(name);
    Bucket *b = hash[hashValue % hashSize];
    while (b) {
		if (b->hashValue == hashValue) {
			if (std::strcmp(name, b->word->Name()) == 0) {
                // match on name, so replace it
                delete b->word;
                b->word = word;
                return true;
			}
		}
		b = b->next;
	}

    // if we get to here, then we did not find anything with
    // the same name, so add it to the table
    //
    Add(word);

    // since we didn't find a match, return false
    //
    return false;
}
