#include "local.hpp"
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
//   a b -- ba
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
//  a -- <stack>
//
// reads in template file a, executes it and places the result in a new stack
// that is pushed onto the current stack
//
bool NFTM::VarFunc_Include::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        stack->PushText("\n*** need to implement VarFunc_Include::Execute ***\n");
    }
    return true;
}
