#ifndef   NFTM_static_src_bin_static_Variable_HPP
#define   NFTM_static_src_bin_static_Variable_HPP

namespace NFTM {
    
    void LoadAllVarFunctions(class SymbolTable *symtab);

    //---------------------------------------------------------------------------
    // Variable
    //    holds value for everything that we're going to manipulate, including
    //    the infamous null value. the only thing that a variable can't hold is
    //    a reference to another variable.
    //
    // TODO - ponder subclassing for the individual types
    //        all should have name
    //
    class Variable {
    public:
        Variable(const char *name);
        Variable(const char *name, class Number   *number);
        Variable(const char *name, class Stack    *stack);
        Variable(const char *name, class Text     *text);
        Variable(const char *name, class Text     *text, int length);
        Variable(const char *name, const char     *text);
        Variable(const char *name, const char     *text, int length);
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

        bool Value(void);
        bool Value(class Function *function);
        bool Value(class Number   *function);
        bool Value(class Stack    *stack);
        bool Value(class Text     *text);
        bool Value(class Text     *text, int length);
        bool Value(const char     *text);
        bool Value(const char     *text, int length);

        virtual bool IsFunction(void) const {
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

        void ClearValues(void);
        void Init(void);

        bool isNull;
        bool isTainted;

        enum { vtOTHER, vtFUNCTION, vtNULL, vtNUMBER, vtSTACK, vtTEXT } kind;

        union {
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

    // VarFunction
    class VarFunction : public Variable {
    public:
        VarFunction(const char *functionName) : Variable(functionName) { }
        ~VarFunction() { }
        
        virtual bool Execute(class SymbolTable *symtab, class Stack *stack);
        bool        IsFunction(void) const {
            return true;
        }
        const char *Kind(void) const {
            return "var.function";
        }
    }; // class VarFunction

    // VarFunc_Concat
    class VarFunc_Concat : public VarFunction {
    public:
        VarFunc_Concat(void) : VarFunction("concat") { }
        ~VarFunc_Concat() { }
        
        bool Execute(class SymbolTable *symtab, class Stack *stack);
    }; // class VarFunc_Concat

    // VarFunc_Include
    class VarFunc_Include : public VarFunction {
    public:
        VarFunc_Include(void) : VarFunction("include") { }
        ~VarFunc_Include() { }

        bool Execute(class SymbolTable *symtab, class Stack *stack);
    }; // class VarFunc_Include
    
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
        VarStack(class Stack *stack);
        ~VarStack();

        bool Execute(class SymbolTable *symtab, class Stack *stack);
        const char *Kind(void) const {
            return "var.stack";
        }

        class Stack *value;
    }; // class VarStack

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
        
        char *value;
    }; // class VarText

} // namespace NFTM

#endif // NFTM_static_src_bin_static_Variable_HPP
