#include "Variable.hpp"
#include "Stack.hpp"
#include "Stream.hpp"
#include "SymbolTable.hpp"
#include "Util.hpp"
#include <stdio.h>


//============================================================================
//
NFTM::Variable::Variable(const char *name_) {
    isNull    = true;
    isTainted = false;
    kind      = vtNULL;
    
    if (name_) {
        StrCopy(name, name_, maxNameLength);
    } else {
        sprintf(name, ".%p", this);
    }
}

//============================================================================
// ~Variable()
//   deletes object
//
NFTM::Variable::~Variable() {
}

//---------------------------------------------------------------------------
//
void NFTM::Variable::Dump(NFTM::OutputStream *os) {
    if (os) {
        os->Write("****** Variable::Dump is BROKEN *****\n");
#if 0
        os->Write("\t\tvar %s is %s%s\n", Name(), IsNull() ? "null " : "", Kind());
        if (!IsNull() && IsText()) {
            char minibuf[64 + 1];
            NFTM::StrCopy(minibuf, val.text->AsCString(), 64);
            char *s = minibuf;
            while (*s && *s != '\n') {
                s++;
            }
            *s = 0;
            os->Write("\t\t\t%s\n", minibuf);
        }
#endif
    }
}

//============================================================================
// Kind(void)
//   returns type of object that word holds.
//
const char *NFTM::Variable::Kind(void) const {
	switch (kind) {
        case vtBOOL:
            return "boolean";
        case vtFUNCTION:
            return "function";
        case vtNULL:
            return "null";
        case vtNUMBER:
            return "number";
        case vtSTACK:
            return "stack";
        case vtTEXT:
            return "text";
        case vtOTHER:
            return "other";
	}
	return "unknown";
}

//============================================================================
// Render(os)
//
bool NFTM::VarBool::Render(NFTM::OutputStream *os) const {
    if (!os) {
        return false;
    }
    os->Write("%s", value ? "true" : "false");
    return true;
}

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
