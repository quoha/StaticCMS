#include "local.hpp"
#include "../Template.hpp"
#include "../Util.hpp"

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
    if (stack) {
        if (stack->Height() < 1) {
            stack->PushText("\n*** error: include requires one text item on the stack **\n\n");
            return false;
        }
        NFTM::Stack::Item *t = stack->PopItem();
        if (!stack->IsText(t)) {
            stack->PushText("\n*** error: include requires one text item on the stack **\n\n");
            return false;
        }
        NFTM::TemplateFile *tmplt = new NFTM::TemplateFile(t->u.text);
        if (!tmplt->Load()) {
            stack->PushFormatted("\n*** error: include failed to load '%s'\n\n", t->u.text);
            return false;
        }
        //stack->PushFormatted("\n*** successfully loaded %s\n", t->u.text);
        NFTM::Stack *includeStack = new NFTM::Stack;
        if (!tmplt->Execute(symtab, includeStack)) {
            stack->PushFormatted("\n*** error: include failed to execute '%s'\n\n", t->u.text);
            return false;
        }
        //stack->PushFormatted("\n*** successfully executed %s\n", t->u.text);

        stack->PushStack(includeStack);

        delete t;
    }
    return true;
}
