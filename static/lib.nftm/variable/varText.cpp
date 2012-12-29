#include "local.hpp"
#include "../Util.hpp"

//============================================================================
// VarText(name, value)
//
NFTM::VarText::VarText(const char *name_, const char *value_) : Variable(name_) {
    kind  = vtOTHER;
    value = NFTM::StrDup(value_);
}

//============================================================================
// ~VarText()
//
NFTM::VarText::~VarText() {
    delete [] value;
}

//============================================================================
// Execute(stack)
//
bool NFTM::VarText::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        stack->Push(this);
    }
    return stack;
}
