#include "local.hpp"

//============================================================================
// F_Include(symtab)
//
NFTM::F_Include::F_Include(NFTM::SymbolTable *symtab) : Function(symtab) {
    name = "include";
    if (symtab) {
        symtab->Add(name, this);
    }
}

//============================================================================
// Execute(symbtab, stack)
//
NFTM::Stack *NFTM::F_Include::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        stack->Push(new NFTM::Variable("~function", "function"));
    }
    return stack;
}