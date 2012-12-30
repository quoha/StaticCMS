#ifndef   NFTM_static_src_bin_static_Stack_HPP
#define   NFTM_static_src_bin_static_Stack_HPP

namespace NFTM {

    //----------------------------------------------------------------------------
    //
    enum stackItemType {siText, siTaintedText, siStack, siStackMarker, siVarReference};

    //----------------------------------------------------------------------------
    //
    struct StackItem {
        struct StackItem *prev;
        struct StackItem *next;
        stackItemType kind;
        union {
            const char     *text;
            class Stack    *stack;
            class Variable *var;
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

        void  PushFormatted(const char *fmt, ...);
        void  PushStack(Stack *stack);
        void  PushStackMarker(void);
        void  PushText(const char *text);
        void  PushText(const char *text, int length);
        void  PushTaintedText(const char *text);
        void  PushVarReference(class Variable *var);
        bool  Render(class OutputStream *os);

        StackItem *PopBottom(void);
        void       PushBottom(StackItem *item);

        StackItem *PopTop(void);
        void       PushTop(StackItem *item);

        bool       CreateStack(void);
        
        int        height;
        StackItem *bottom;
        StackItem *top;
    }; // class Stack

} // namespace NFTM

#endif // NFTM_static_src_bin_static_Stack_HPP
