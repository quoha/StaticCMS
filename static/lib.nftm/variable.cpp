#include "Variable.hpp"
#include "Function.hpp"
#include "Stack.hpp"
#include "Stream.hpp"
#include "SymbolTable.hpp"
#include "Text.hpp"
#include "Util.hpp"
#include <stdio.h>


//============================================================================
//
NFTM::Variable::Variable(const char *name_) {
    if (name_) {
        StrCopy(name, name_, maxNameLength);
    } else {
        sprintf(name, ".%p", this);
    }

    isNull    = true;
    isTainted = false;
    kind      = vtNULL;
    u.null    = 0;
}

//============================================================================
//
NFTM::Variable::Variable(const char *name_, vrtKind kind_) {
    if (name_) {
        StrCopy(name, name_, maxNameLength);
    } else {
        sprintf(name, ".%p", this);
    }

    isNull    = true;
    isTainted = false;
    kind      = kind_;
    u.null    = 0;
}

//============================================================================
//
NFTM::Variable::Variable(const char *name_, NFTM::Function *function) {
    if (name_) {
        StrCopy(name, name_, maxNameLength);
    } else {
        sprintf(name, ".%p", this);
    }
    
    isNull       = function ? false : true;
    isTainted    = false;
    kind         = vtFUNCTION;
    u.function   = function;
}

//============================================================================
//
NFTM::Variable::Variable(const char *name_, NFTM::Stack *stack) {
    if (name_) {
        StrCopy(name, name_, maxNameLength);
    } else {
        sprintf(name, ".%p", this);
    }
    
    isNull       = stack ? false : true;
    isTainted    = false;
    kind         = vtSTACK;
    u.stack      = stack;
}

//============================================================================
//
NFTM::Variable::Variable(const char *name_, NFTM::Text *text) {
    if (name_) {
        StrCopy(name, name_, maxNameLength);
    } else {
        sprintf(name, ".%p", this);
    }
    
    isNull       = text ? text->IsNull()    : true;
    isTainted    = text ? text->IsTainted() : false;
    kind         = vtTEXT;
    u.text       = text;
}

//============================================================================
//
NFTM::Variable::Variable(const char *name_, NFTM::VarBoolean *varBoolean) {
    if (name_) {
        StrCopy(name, name_, maxNameLength);
    } else {
        sprintf(name, ".%p", this);
    }
    
    isNull       = varBoolean ? false : true;
    isTainted    = false;
    kind         = vtBOOLEAN;
    u.boolean    = varBoolean ? varBoolean->value : false;
}

//============================================================================
//
NFTM::Variable::Variable(const char *name_, NFTM::VarNumber *varNumber) {
    if (name_) {
        StrCopy(name, name_, maxNameLength);
    } else {
        sprintf(name, ".%p", this);
    }
    
    isNull       = varNumber ? false : true;
    isTainted    = false;
    kind         = vtNUMBER;
    u.number     = varNumber ? varNumber->value : 0;
}

//============================================================================
//
NFTM::Variable::Variable(const char *name_, NFTM::Variable *variable) {
    if (name_) {
        StrCopy(name, name_, maxNameLength);
    } else {
        sprintf(name, ".%p", this);
    }

    isNull    = variable->isNull;
    isTainted = variable->isTainted;
    kind      = variable->kind;
    u.null    = variable->u.null;
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
        //os->Write("****** Variable::Dump is BROKEN *****\n");
        os->Write("\t\tvar %s is %s%s\n", Name(), IsNull() ? "null " : "", Kind());
        if (!IsNull() && IsText()) {
            char minibuf[64 + 1];
            NFTM::StrCopy(minibuf, u.text->text, 64);
            char *s = minibuf;
            while (*s && *s != '\n') {
                s++;
            }
            *s = 0;
            os->Write("\t\t\t%s\n", minibuf);
        }
    }
}

//============================================================================
// Execute(stack)
//
bool NFTM::Variable::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        NFTM::OutputStream *errlog = symtab->ErrorLog();
        
        switch (kind) {
            case vtFUNCTION:
                if (isNull) {
                    if (errlog) {
                        errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                        errlog->Write("\tunable to execute null word %s\n", Name());
                    }
                    return false;
                }
                return u.function->Execute(symtab, stack);
            case vtBOOLEAN:
                stack->PushBoolean(isNull ? false : u.boolean);
                break;
            case vtNULL:
                stack->PushNull();
                break;
            case vtNUMBER:
            case vtSTACK:
            case vtTEXT:
            case vtOTHER:
                if (errlog) {
                    errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                    errlog->Write("\tinternal error - variable.execute doesn't understand %s (%d)\n", Kind(), kind);
                }
                return false;
        }
    }
    return true;
}


//============================================================================
// Kind(void)
//   returns type of object that word holds.
//
const char *NFTM::Variable::Kind(void) const {
	switch (kind) {
        case vtBOOLEAN:
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
//
bool NFTM::Variable::Render(class OutputStream *os) const {
    return false;
}
