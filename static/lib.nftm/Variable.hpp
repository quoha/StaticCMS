#ifndef   NFTM_static_src_bin_static_Variable_HPP
#define   NFTM_static_src_bin_static_Variable_HPP

namespace NFTM {

    enum vrtKind { vtOTHER, vtBOOLEAN, vtFUNCTION, vtNULL, vtNUMBER, vtSTACK, vtTEXT };

    //---------------------------------------------------------------------------
    // Variable
    //    holds value for everything that we're going to manipulate, including
    //    the infamous null value. the only thing that a variable can't hold is
    //    a reference to another variable.
    //
    // NOTE are variables immutable?
    //
    class Variable {
    public:
        Variable(const char *name);
        Variable(const char *name, vrtKind kind);
        Variable(const char *name, class Function   *function);
        Variable(const char *name, class Stack      *stack);
        Variable(const char *name, class Text       *text);
        Variable(const char *name, class VarBoolean *varBoolean);
        Variable(const char *name, class VarNumber  *varNumber);
        ~Variable();

        bool Execute(class SymbolTable *symtab, class Stack *stack);
        const char *Kind(void) const;

        const char *Name(void) const {
            return name;
        }

        bool Render(class OutputStream *os) const;

        bool IsBoolean(void) const {
            return kind == vtBOOLEAN;
        }
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
        bool IsTaintedText(void) const {
            return kind == vtTEXT && isTainted;
        }
        bool IsText(void) const {
            return kind == vtTEXT;
        }

        void Dump(class OutputStream *os);

        // initialized when created, never changed
        //
        static const int maxNameLength = 64;
        char    name[maxNameLength + 1];
        bool    isNull;
        bool    isTainted;
        vrtKind kind;

        union {
            bool            boolean;
            class Function *function;
            void           *null;
            int             number;
            class Stack    *stack;
            class Text     *text;
        } u;
    }; // class Variable

    // VarBoolean
    class VarBoolean {
    public:
        VarBoolean(bool value_) { value = value_; }
        ~VarBoolean() { }

        bool value;
    }; // class VarBoolean

    // VarNumber
    class VarNumber {
    public:
        VarNumber(int value_) { value = value_; }
        ~VarNumber();
        
        int value;
    }; // class VarNumber

} // namespace NFTM

#endif // NFTM_static_src_bin_static_Variable_HPP
