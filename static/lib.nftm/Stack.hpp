#ifndef   NFTM_static_src_bin_static_Stack_HPP
#define   NFTM_static_src_bin_static_Stack_HPP

#include <list>

namespace NFTM {
    
    //----------------------------------------------------------------------------
    // Stack
    //   manage a stack of pointers to three types of objects:
    //      * tainted text
    //      * untainted text
    //      * stack
    //
    class Stack {
    public:
        Stack(void);
        ~Stack();
        
        // the classic stack interface
        //  * Push adds     an item to   the top of the stack
        //  * Pop  removes the item from the top of the stack
        //
        class Variable *Pop(void) {
            return Top();
        }
        class Variable *Push(class Variable *variable) {
            return Top(variable);
        }
        
        // don't tell anyone, but we are really a double-ended queue
        //
        //  * bottom is the first item added
        //  * top    is the last  item added
        //
        class Variable *Bottom(void);                       // pop  variable from bottom
        class Variable *Bottom(class Variable *variable);   // push variable to   bottom
        class Variable *Top(void);                          // pop  variable from top
        class Variable *Top(class Variable *variable);      // push variable to   top
        
        struct StackNode {
            struct StackNode *prev;  // towards bottom of stack
            class  Variable  *variable;
            struct StackNode *next;  // towards top    of stack
        } *bottom, *top;
        
        struct Item {
            enum {siText, siTaintedText, siStack, siVarReference} kind;
            union {
                const char     *text;
                Stack          *stack;
                class Variable *var;
            } u;
        };
        
        std::list<struct Item *> items;
        
        Item *PopItem(void);
        void  PushStack(Stack *stack);
        void  PushText(const char *text);
        void  PushTaintedText(const char *text);
        void  PushVarReference(class Variable *var);
        bool  Render(class OutputStream *os);
    }; // class Stack
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_Stack_HPP
