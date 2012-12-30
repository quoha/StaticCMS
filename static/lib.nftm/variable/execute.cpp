#include "local.hpp"
#include "../Stream.hpp"
#include "../Template.hpp"
#include "../Util.hpp"
#include <stdio.h>

//============================================================================
// Execute(stack)
//
bool NFTM::VarFunction::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    NFTM::OutputStream *errlog = symtab->ErrorLog();
    if (errlog) {
        errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
        errlog->Write("\tcalled VarFunction::Execute directly (or didn't override)\n");
    }
    return false;
}

//============================================================================
// Execute(stack)
//   t1 t2 -- t2t1
//
bool NFTM::VarFunc_Concat::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        NFTM::StackItem *b = stack->Pop();
        NFTM::StackItem *a = stack->Pop();

        if (!a || !b) {
            NFTM::OutputStream *errlog = symtab->ErrorLog();
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tconcat requires two text items on the stack\n");
            }
            return false;
        }
        if (!stack->IsText(a) || !stack->IsText(b)) {
            NFTM::OutputStream *errlog = symtab->ErrorLog();
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tconcat requires two text items on the stack\n");
            }
            return false;
        }
        stack->PushText(NFTM::StrCat(b->u.text, a->u.text));
        delete a;
        delete b;
    }
    return true;
}

//============================================================================
// Execute(stack)
//  t -- <stack>
//
// reads in template file 't', executes it and places the result in a new stack
// that is pushed onto the current stack
//
bool NFTM::VarFunc_Include::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        NFTM::StackItem *t = stack->Pop();

        if (!t) {
            NFTM::OutputStream *errlog = symtab->ErrorLog();
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tinclude requires at least one text item on the stack\n");
            }
            return false;
        }

        if (!stack->IsText(t)) {
            NFTM::OutputStream *errlog = symtab->ErrorLog();
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tinclude text item on the stack, not %s\n", "fix this reference to t->Kind()");
            }
            return false;
        }
        
        NFTM::TemplateFile *tmplt = new NFTM::TemplateFile(t->u.text);
        if (!tmplt->Load()) {
            NFTM::OutputStream *errlog = symtab->ErrorLog();
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tinclude failed to load '%s'\n", t->u.text);
            }
            return false;
        }
        
        NFTM::Stack *includeStack = new NFTM::Stack;
        if (!tmplt->Execute(symtab, includeStack)) {
            NFTM::OutputStream *errlog = symtab->ErrorLog();
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tinclude failed to execute '%s'\n", t->u.text);
            }
            return false;
        }
        
        stack->PushStack(includeStack);
        
        delete t;
    }
    return true;
}

//============================================================================
// Execute(stack)
//  x <stackMarker> y z -- x { y z }
//
// searches stack for marker. removes the marker, moves everything from that
// point to a new stack and then pushes that stack onto the current stack
//
bool NFTM::VarFunc_PopStack::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        // error if not found
        //
        if (!stack->CreateStack()) {
            NFTM::OutputStream *errlog = symtab->ErrorLog();
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tfailed to find matching '{' in stack\n");
            }
            return false;
        }
    }

    return true;
}

//============================================================================
// Execute(stack)
//  ~ -- ~ <stackMarker>
//
// pushes a stack marker onto the current stack
//
bool NFTM::VarFunc_PushStack::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        stack->PushStackMarker();
    }
    return true;
}
