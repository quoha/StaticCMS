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
    // the classic stack interface
    //  * Push adds     an item to   the top of the stack
    //  * Pop  removes the item from the top of the stack
    //
    class Stack {
    public:
        Stack(void);
        ~Stack();

        struct Item {
            enum {siText, siTaintedText, siStack, siVarReference} kind;
            union {
                const char     *text;
                Stack          *stack;
                class Variable *var;
            } u;
        };
        
        std::list<struct Item *> items;
        
        int   Height(void) const {
            return (int)(items.size());
        }
        bool  IsText(Item *i) const {
            return i->kind == Item::siText;
        }
        Item *PopItem(void);
        void  PushFormatted(const char *fmt, ...);
        void  PushStack(Stack *stack);
        void  PushText(const char *text);
        void  PushText(const char *text, int length);
        void  PushTaintedText(const char *text);
        void  PushVarReference(class Variable *var);
        bool  Render(class OutputStream *os);
    }; // class Stack
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_Stack_HPP
