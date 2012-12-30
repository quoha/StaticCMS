#include "local.hpp"
#include "../Stream.hpp"
#include "../Template.hpp"
#include "../Util.hpp"
#include <stdio.h>

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
// Execute(stack)
//   t1 t2 -- t2t1
//
bool NFTM::VarFunc_Concat::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        if (stack->Height() < 2) {
            stack->PushText("\n*** error: concat requires two text items on the stack **\n\n");
            return false;
        }
        NFTM::Stack::Item *b = stack->PopItem();
        NFTM::Stack::Item *a = stack->PopItem();
        if (!stack->IsText(a) || !stack->IsText(b)) {
            stack->PushText("\n*** error: concat requires two text items on the stack **\n\n");
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
    NFTM::OutputStream *errlog = symtab->ErrorLog();
    
    if (stack) {
        if (stack->Height() < 1) {
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tinclude requires at least one text item on the stack\n");
            }
            return false;
        }
        
        NFTM::Stack::Item *t = stack->PopItem();
        if (!stack->IsText(t)) {
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tinclude text item on the stack, not %s\n", "fix this reference to t->Kind()");
            }
            return false;
        }
        
        NFTM::TemplateFile *tmplt = new NFTM::TemplateFile(t->u.text);
        if (!tmplt->Load()) {
            if (errlog) {
                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                errlog->Write("\tinclude failed to load '%s'\n", t->u.text);
            }
            return false;
        }
        
        NFTM::Stack *includeStack = new NFTM::Stack;
        if (!tmplt->Execute(symtab, includeStack)) {
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
//  ~ -- ~ <stackMarker>
//
// pushes a stack marker onto the current stack
//
bool NFTM::VarFunc_PushStack::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        stack->PushVarReference(this);
    }
    return true;
}
