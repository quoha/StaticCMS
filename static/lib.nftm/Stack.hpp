#ifndef   NFTM_static_src_bin_static_Stack_HPP
#define   NFTM_static_src_bin_static_Stack_HPP

namespace NFTM {

    //----------------------------------------------------------------------------
    //
    enum stackItemType {siBoolean, siFunction, siNull, siStack, siStackMarker, siText, siVariable};

    //----------------------------------------------------------------------------
    //
    struct StackItem {
        struct StackItem *prev;
        struct StackItem *next;
        stackItemType kind;
        union {
            bool            boolean;
            class Function *function;
            class Stack    *stack;
            class Text     *text;
            class Variable *variable;
            void           *null;
        } u;
    };

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

        int   Height(void) const {
            return height;
        }
        bool  IsText(StackItem *i) const {
            return i->kind == siText;
        }

        StackItem *Pop(void) {
            return PopTop();
        }
        void       Push(StackItem *item) {
            PushTop(item);
        }

        void  PushBoolean(bool boolean);
        void  PushFormatted(const char *fmt, ...);
        void  PushNull(void);
        void  PushStack(Stack *stack);
        void  PushStackMarker(void);
        void  PushText(class Text *text);
#if 0
        void  PushText(const char *text);
        void  PushText(const char *text, int length);
        void  PushTaintedText(const char *text);
#endif
        void  PushVarReference(class Variable *var);

        bool  Render(class OutputStream *os, class OutputStream *errlog);

        StackItem *PopBottom(void);
        void       PushBottom(StackItem *item);

        StackItem *PopTop(void);
        void       PushTop(StackItem *item);

        bool       CreateStack(void);
        void       Dump(class OutputStream *os);
        
        int        height;
        StackItem *bottom;
        StackItem *top;
    }; // class Stack

} // namespace NFTM

#endif // NFTM_static_src_bin_static_Stack_HPP
