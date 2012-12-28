#include "local.hpp"

//============================================================================
// Add(function)
//
NFTM::Word *NFTM::SymbolTable::Add(NFTM::Function *function) {
	return Add(new NFTM::Word(function));
}

//============================================================================
// Add(var)
//
NFTM::Word *NFTM::SymbolTable::Add(NFTM::Variable *var) {
	return Add(new NFTM::Word(var));
}

//============================================================================
// Add(var)
//
NFTM::Word *NFTM::SymbolTable::Add(const char *name, const char *value) {
	return Add(new NFTM::Variable(name, value));
}

//============================================================================
// Add(word)
//
NFTM::Word *NFTM::SymbolTable::Add(NFTM::Word *word) {
	Bucket     *b    = new Bucket();

	b->word      = word;
	b->hashValue = Hash(word->Name());
	b->next      = hash[b->hashValue % hashSize];

	hash[b->hashValue % hashSize] = b;

	return word;
}
