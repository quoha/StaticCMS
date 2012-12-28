#include "local.hpp"

//============================================================================
// Update(name, value)
//   if name is in the table and is a variable,
//      update its value
//   otherwise, if name is not in the table,
//      create a new variable with name and value and add it to the table
//
// RETURN
//   true   the symbol table was changed
//   false  the symbol table was not changed
//
bool NFTM::SymbolTable::Update(const char *name, const char *value) {
    // search the table for the first item with this name
    //
	NFTM::Word *word = Lookup(name);
    
	if (!word) {
        // name does not exist, so add it as a new variable
        //
		Add(name, value);

		return true;
	} else if (word->IsVariable()) {
        // name does exist and is a variable, so update its value
        //
		word->AsVariable()->Value(value);

		return true;
	}
    
	return false;
}
