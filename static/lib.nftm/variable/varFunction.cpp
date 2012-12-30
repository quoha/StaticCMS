#include "local.hpp"
#include "../Util.hpp"

//============================================================================
// VarFunction(name, value)
//
NFTM::VarFunction::VarFunction(const char *name_) : Variable(name_) {
}

//============================================================================
// ~VarFunction()
//
NFTM::VarFunction::~VarFunction() {
}

//============================================================================
// Execute(stack)
//
bool NFTM::VarFunction::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        stack->PushText("error: called VarFunction::Execute directly (or didn't override)\n");
    }
    return false;
}

//============================================================================
// VarFunc_Include()
//
NFTM::VarFunc_Include::VarFunc_Include(void) : VarFunction("include") {
}

//============================================================================
// ~VarFunc_Include()
//
NFTM::VarFunc_Include::~VarFunc_Include() {
}

//============================================================================
// Execute(stack)
//
bool NFTM::VarFunc_Include::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        stack->PushText("\n*** need to implement VarFunc_Include::Execute ***\n");
    }
    return true;
}
