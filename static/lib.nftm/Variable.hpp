#ifndef   NFTM_static_src_bin_static_Variable_HPP
#define   NFTM_static_src_bin_static_Variable_HPP

namespace NFTM {
    
    //---------------------------------------------------------------------------
    // Variable
    //    holds value for everything that we're going to manipulate, including
    //    the infamous null value. the only thing that a variable can't hold is
    //    a reference to another variable.
    //
    class Variable {
    public:
        Variable(const char *name);
        Variable(const char *name, class Function *function);
        Variable(const char *name, class Number   *number);
        Variable(const char *name, class Stack    *stack);
        Variable(const char *name, class Text     *text);
        Variable(const char *name, class Text     *text, int length);
        Variable(const char *name, const char     *text);
        Variable(const char *name, const char     *text, int length);
        ~Variable();

        const char *Kind(void) const;

        const char *Name(void) const {
            return name;
        }

        bool Value(void);
        bool Value(class Function *function);
        bool Value(class Number   *function);
        bool Value(class Stack    *stack);
        bool Value(class Text     *text);
        bool Value(class Text     *text, int length);
        bool Value(const char     *text);
        bool Value(const char     *text, int length);

        bool IsFunction(void) const {
            return kind == vtFUNCTION;
        }
        bool IsNull(void) const {
            return isNull;
        }
        bool IsNumber(void) const {
            return kind == vtNUMBER;
        }
        bool IsStack(void) const {
            return kind == vtSTACK;
        }
        bool IsTainted(void) const {
            return isTainted;
        }
        bool IsText(void) const {
            return kind == vtTEXT;
        }

        class Function *AsFunction(void) {
            return kind == vtFUNCTION ? val.function : 0;
        }
        class Number   *AsNumber(void) {
            return kind == vtNUMBER ? val.number : 0;
        }
        class Stack    *AsStack(void) {
            return kind == vtSTACK ? val.stack : 0;
        }
        class Text     *AsText(void) {
            return kind == vtTEXT ? val.text : 0;
        }

        void Dump(class OutputStream *os);
    private:
        void ClearValues(void);
        void Init(void);

        bool isNull;
        bool isTainted;

        enum { vtFUNCTION, vtNULL, vtNUMBER, vtSTACK, vtTEXT } kind;

        union {
            class Function *function;
            class Number   *number;
            class Stack    *stack;
            class Text     *text;
            void           *null;
        } val;

        // initialized when created, never changed
        //
        static const int maxNameLength = 64;
        char name[maxNameLength + 1];
    }; // class Variable
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_Variable_HPP
