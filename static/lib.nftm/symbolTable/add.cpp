#include "local.hpp"

//============================================================================
// Add(name, number)
//
NFTM::Variable *NFTM::SymbolTable::Add(const char *name, NFTM::Number *number) {
	return Add(new NFTM::Variable(name, number));
}

//============================================================================
// Add(name, stack)
//
NFTM::Variable *NFTM::SymbolTable::Add(const char *name, NFTM::Stack *stack) {
	return Add(new NFTM::Variable(name, stack));
}

//============================================================================
// Add(name, text)
//
NFTM::Variable *NFTM::SymbolTable::Add(const char *name, NFTM::Text *text) {
	return Add(new NFTM::Variable(name, text));
}

//============================================================================
// Add(name, text, length)
//
NFTM::Variable *NFTM::SymbolTable::Add(const char *name, NFTM::Text *text, int length) {
	return Add(new NFTM::Variable(name, text, length));
}

//============================================================================
// Add(name, cstring)
//
NFTM::Variable *NFTM::SymbolTable::Add(const char *name, const char *text) {
	return Add(new NFTM::Variable(name, text));
}

//============================================================================
// Add(name, cstring, length)
//
NFTM::Variable *NFTM::SymbolTable::Add(const char *name, const char *text, int length) {
	return Add(new NFTM::Variable(name, text, length));
}

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
