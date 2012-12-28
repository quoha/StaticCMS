#include "local.hpp"

//============================================================================
// GetVar(name)
//   returns CGI variables from environment
//
NFTM::Variable *NFTM::CGI::GetVar(const char *name) {
	NFTM::Word     *word = symtab->Lookup(name);
	NFTM::Variable *var  = word ? word->AsVariable() : 0;

	return var;
}
