#include "local.hpp"
#include "../Util.hpp"

//============================================================================
// VarNumber(name, value)
//
NFTM::VarNumber::VarNumber(const char *name_, int value_) : Variable(name_) {
    kind  = vtOTHER;
    value = value_;
}

//============================================================================
// ~VarNumber()
//
NFTM::VarNumber::~VarNumber() {
}

//============================================================================
// Execute(stack)
//
bool NFTM::VarNumber::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        stack->PushVarReference(this);
    }
    return true;
}
