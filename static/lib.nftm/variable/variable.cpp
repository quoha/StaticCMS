#include "../Variable.hpp"
#include "../Stack.hpp"
#include "../Stream.hpp"
#include "../SymbolTable.hpp"
#include "../Util.hpp"

//============================================================================
// Execute(stack)
//
bool NFTM::VarFunction::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        stack->PushVarReference(this);
    }
    return true;
}

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
        stack->PushVarReference(this);
    }
    return true;
}

//============================================================================
// Render(os)
//
bool NFTM::VarText::Render(NFTM::OutputStream *os) const {
    if (!os) {
        return false;
    }
    if (value && *value) {
        os->Write("%s", value);
    }
    return true;
}

//============================================================================
// VarStack(name, value)
//
NFTM::VarStack::VarStack(const char *name_, NFTM::Stack *value_) : Variable(name_) {
    kind  = vtOTHER;
    value = value_;
}

//============================================================================
// ~VarStack()
//
NFTM::VarStack::~VarStack() {
    delete value;
}

//============================================================================
// Execute(symtab, stack)
//
bool NFTM::VarStack::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        stack->PushVarReference(this);
    }
    return true;
}

//============================================================================
// Kind()
//
const char *NFTM::VarStack::Kind(void) const {
    return "var.stack";
}
