#ifndef   NFTM_static_src_bin_static_Variable_HPP
#define   NFTM_static_src_bin_static_Variable_HPP

namespace NFTM {

    enum vrtKind { vtOTHER, vtBOOL, vtFUNCTION, vtNULL, vtNUMBER, vtSTACK, vtTEXT };

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
        virtual ~Variable();

        virtual bool Execute(class SymbolTable *symtab, class Stack *stack) {
            return false;
        }

        virtual const char *Kind(void) const;

        const char *Name(void) const {
            return name;
        }

        virtual bool Render(class OutputStream *os) const {
            return false;
        }

        bool IsConst(void) const {
            return false;
        }
        bool IsFinal(void) const {
            return false;
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
        bool IsText(void) const {
            return kind == vtTEXT;
        }

        void Dump(class OutputStream *os);

        // initialized when created, never changed
        //
        static const int maxNameLength = 64;
        char name[maxNameLength + 1];
        bool isNull;
        bool isTainted;
        vrtKind kind;
        
        union {
            bool            asBool;
            class Function *asFunction;
        } v;
    }; // class Variable

    // VarBool
    class VarBool : public Variable {
    public:
        VarBool(const char *functionName, bool value_) : Variable(functionName) {
            kind = vtBOOL;
            value = value_;
            v.asBool = value_;
        }
        ~VarBool() { }
        
        const char *Kind(void) const {
            return "var.boolean";
        }

        bool value;
    }; // class VarBool

    // VarFunction
    class VarFunction : public Variable {
    public:
        VarFunction(const char *functionName, class Function *function_) : Variable(functionName) {
            kind = vtFUNCTION;
            function = function_;
            v.asFunction = function_;
        }
        ~VarFunction() { }

        bool Execute(class SymbolTable *symtab, class Stack *stack);

        const char *Kind(void) const {
            return "var.function";
        }
        
        class Function *function;
    }; // class VarFunction

    // VarNull
    class VarNull : public Variable {
    public:
        VarNull(const char *name);
        ~VarNull();

        bool Execute(class SymbolTable *symtab, class Stack *stack);
        const char *Kind(void) const {
            return "var.null";
        }
    }; // class VarNull

    // VarNumber
    class VarNumber : public Variable {
    public:
        VarNumber(const char *name, int value);
        ~VarNumber();
        
        bool Execute(class SymbolTable *symtab, class Stack *stack);
        const char *Kind(void) const {
            return "var.number";
        }
        
        int value;
    }; // class VarNumber

    // VarStack
    class VarStack : public Variable {
    public:
        VarStack(const char *name_, class Stack *stack);
        ~VarStack();

        bool        Execute(class SymbolTable *symtab, class Stack *stack);
        const char *Kind(void) const;

        class Stack *value;
    }; // class VarStack

    // VarOutputStream
    class VarOutputStream : public Variable {
    public:
        VarOutputStream(const char *name_, class OutputStream *value_) : Variable(name_) { value = value_; }
        ~VarOutputStream();

        bool Execute(class SymbolTable *symtab, class Stack *stack) {
            return false;
        }
        const char *Kind(void) const {
            return "var.outputStream";
        }

        class OutputStream *value;
    }; // class VarStream

    // VarText
    class VarText : public Variable {
    public:
        VarText(const char *name, const char *text);
        ~VarText();
        
        bool Execute(class SymbolTable *symtab, class Stack *stack);
        const char *Kind(void) const {
            return "var.text";
        }
        bool Render(class OutputStream *os) const;
        const char *Value(void) const {
            return value;
        }

        char *value;
    }; // class VarText

    // VarTaintedText
    class VarTaintedText : public VarText {
    public:
        VarTaintedText(const char *name, const char *text);
        ~VarTaintedText();
        
        bool Execute(class SymbolTable *symtab, class Stack *stack);
        const char *Kind(void) const {
            return "var.text.tainted";
        }
        bool Render(class OutputStream *os) const;
        const char *Value(void) const {
            return value;
        }
        
        char *value;
    }; // class VarTaintedText

} // namespace NFTM

#endif // NFTM_static_src_bin_static_Variable_HPP
