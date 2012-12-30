#include "../Stack.hpp"
#include "../Variable.hpp"
#include "../Stream.hpp"

//============================================================================
//
NFTM::Stack::Item *NFTM::Stack::PopItem(void) {
    Item *i = 0;
    if (!items.empty()) {
        i = items.front();
        items.pop_front();
    }
    return i;
}

//============================================================================
//
void NFTM::Stack::PushStack(NFTM::Stack *stack) {
    Item *i    = new Item;
    i->kind    = Item::siStack;
    i->u.stack = stack;
    items.push_front(i);
}

//============================================================================
//
void NFTM::Stack::PushText(const char *text) {
    Item *i   = new Item;
    i->kind   = Item::siText;
    i->u.text = text;
    items.push_front(i);
}

//============================================================================
//
void NFTM::Stack::PushTaintedText(const char *text) {
    Item *i   = new Item;
    i->kind   = Item::siTaintedText;
    i->u.text = text;
    items.push_front(i);
}

//============================================================================
//
void NFTM::Stack::PushVarReference(NFTM::Variable *var) {
    Item *i  = new Item;
    i->kind  = Item::siText;
    i->u.var = var;
    items.push_front(i);
}

//============================================================================
// Render(os)
//
bool NFTM::Stack::Render(NFTM::OutputStream *os) {
    if (!os) {
        return false;
    }
    
    while (!items.empty()) {
        Item *i = items.front();
        switch (i->kind) {
            case Item::siTaintedText:
                os->Write("%s", i->u.text);
                break;
            case Item::siText:
                os->Write("%s", i->u.text);
                break;
            case Item::siStack:
                if (!i->u.stack->Render(os)) {
                    return false;
                }
                break;
            case Item::siVarReference:
                if (!i->u.var->Render(os)) {
                    return false;
                }
                break;
        }
        delete i;
        items.pop_front();
    }
    
    return true;
}