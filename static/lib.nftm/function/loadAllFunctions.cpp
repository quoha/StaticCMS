#include "local.hpp"

//============================================================================
// LoadAllFunctions(symtab)
//
bool NFTM::LoadAllFunctions(NFTM::SymbolTable *symtab) {
    if (symtab) {
        new NFTM::F_Include(symtab);
    }
    return true;
}
