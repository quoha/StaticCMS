#include "../Stack.hpp"
#include "../Stream.hpp"
#include "../Util.hpp"
#include "../Variable.hpp"
#include <stdio.h>
#include <stdarg.h>

//============================================================================
// Stack()
//   create an empty stack
//
NFTM::Stack::Stack(void) {
    bottom = 0;
    top    = 0;
    height = 0;
}

//============================================================================
// ~Stack()
//
NFTM::Stack::~Stack() {
}

//============================================================================
//
bool NFTM::Stack::CreateStack(void) {
    NFTM::StackItem *stackMarker = top;
    while (stackMarker && stackMarker->kind != siStackMarker) {
        stackMarker = stackMarker->prev;
    }
    
    // no stack marker found
    //
    if (!stackMarker) {
        return false;
    }
    
    // unlink the current item from this stack
    //
    top = stackMarker->prev;
    if (!top) {
        top = bottom = 0;
    }
    
    // we don't want to put the stack marker into the new stack
    //
    NFTM::StackItem *topOfNewStack = stackMarker->next;
    if (topOfNewStack) {
        topOfNewStack->prev = 0;
    }
    
    // adios, stack marker
    //
    stackMarker->prev = 0;
    stackMarker->next = 0;
    delete stackMarker;

    // create a new stack, push the split off items to it
    //
    NFTM::Stack *stack = new NFTM::Stack;
    if (topOfNewStack) {
        stack->PushTop(topOfNewStack);
    }

    // push the new stack onto the current stack
    //
    PushStack(stack);

    return true;
}

//============================================================================
//
NFTM::StackItem *NFTM::Stack::PopBottom(void) {
    NFTM::StackItem *item = bottom;
    if (bottom) {
        height--;
        bottom = bottom->next;
        if (bottom) {
            bottom->prev = 0;
        } else {
            top = bottom = 0;
        }
        item->next = 0;
        item->prev = 0;
    }
    return item;
}

//============================================================================
//
NFTM::StackItem *NFTM::Stack::PopTop(void) {
    NFTM::StackItem *item = top;
    if (top) {
        height--;
        top = top->prev;
        if (top) {
            top->next = 0;
        } else {
            top = bottom = 0;
        }
        item->next = 0;
        item->prev = 0;
    }
    return item;
}

//============================================================================
//
void NFTM::Stack::PushBottom(StackItem *item) {
    if (item) {
        height++;
        if (bottom) {
            item->prev   = 0;
            item->next   = bottom;
            bottom->prev = item;
            bottom       = item;
        } else {
            top = bottom = item;
            item->prev = 0;
            item->next = 0;
        }
    }
}

//============================================================================
//
void NFTM::Stack::PushTop(StackItem *item) {
    if (item) {
        height++;
        if (top) {
            item->prev = top;
            item->next = 0;
            top->next  = item;
            top        = item;
        } else {
            top = bottom = item;
            item->prev = 0;
            item->next = 0;
        }
    }
}

//============================================================================
// PushFormatted(fmt, ...)
//
void NFTM::Stack::PushFormatted(const char *fmt, ...) {
    char data[256];
    
	if (fmt && *fmt) {
		va_list ap;
		va_start(ap, fmt);
		vsnprintf(data, 256, fmt, ap);
        data[255] = 0;
		va_end(ap);
        PushText(NFTM::StrDup(data));
	}
}

//============================================================================
//
void NFTM::Stack::PushStack(NFTM::Stack *stack) {
    NFTM::StackItem *item = new NFTM::StackItem;
    item->kind    = siStack;
    item->u.stack = stack;
    PushTop(item);
}

//============================================================================
//
void NFTM::Stack::PushStackMarker(void) {
    NFTM::StackItem *item = new NFTM::StackItem;
    item->kind    = siStackMarker;
    item->u.null  = 0;
    PushTop(item);
}

//============================================================================
//
void NFTM::Stack::PushText(const char *text) {
    NFTM::StackItem *item = new NFTM::StackItem;
    item->kind   = siText;
    item->u.text = text;
    PushTop(item);
}

//============================================================================
//
void NFTM::Stack::PushTaintedText(const char *text) {
    NFTM::StackItem *item = new NFTM::StackItem;
    item->kind   = siTaintedText;
    item->u.text = text;
    PushTop(item);
}

//============================================================================
//
void NFTM::Stack::PushVarReference(NFTM::Variable *var) {
    NFTM::StackItem *item = new NFTM::StackItem;
    item->kind  = siVariable;
    item->u.var = var;
    PushTop(item);
}

//============================================================================
// Render(os)
//
bool NFTM::Stack::Render(NFTM::OutputStream *os) {
    if (!os) {
        return false;
    }
    
    NFTM::StackItem *curr = bottom;
    while (curr) {
        switch (curr->kind) {
            case siBoolean:
                os->Write("%s", curr->u.boolean ? "true" : "false");
                break;
            case siFunction:
                // should never happen
                //
                break;
            case siStack:
                if (!curr->u.stack->Render(os)) {
                    return false;
                }
                break;
            case siStackMarker:
                break;
            case siTaintedText:
                os->Write("%s", curr->u.text);
                break;
            case siText:
                os->Write("%s", curr->u.text);
                break;
            case siVariable:
                if (!curr->u.var->Render(os)) {
                    return false;
                }
                break;
        }
        
        NFTM::StackItem *tmp = curr;
        curr = curr->next;
        delete tmp;
    }
    
    return true;
}
