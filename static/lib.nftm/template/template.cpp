#include "../Template.hpp"

//---------------------------------------------------------------------------
// Execute(symtab, stack)
//
bool NFTM::Template::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (!symtab || !stack) {
        return false;
    }

    return true;
}
