#include "local.hpp"

//============================================================================
// SetVar(var, value)
//   sets CGI variables
//
bool NFTM::CGI::SetVar(const char *name, const char *value) {
	NFTM::Word *word = symtab->Lookup(name);

	if (!word) {
		symtab->Add(new NFTM::Variable(name, value));
		return true;
	} else if (word->IsVariable()) {
		word->AsVariable()->Value(value);
		return true;
	}

	return false;
}
