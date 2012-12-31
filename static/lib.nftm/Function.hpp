#ifndef   NFTM_static_src_bin_static_lib_nftm_Function_HPP
#define   NFTM_static_src_bin_static_lib_nftm_Function_HPP

namespace NFTM {
    
    void LoadAllFunctions(class SymbolTable *symtab);
    
    //---------------------------------------------------------------------------
    // Function
    //    most functions will manipulate the stack. a few need access to the
    //    symbol table to get variables and functions.
    //
    class Function {
    public:
        Function(const char *name_) {
            name = name_;
        }
        virtual ~Function() {
            // nothing much to do here
        }

        virtual bool Execute(class SymbolTable *symtab, class Stack *stack);
        const char  *Name(void) const {
            return name;
        }

        const char *name;
        
    }; // class Function

    //---------------------------------------------------------------------------
    // Func_Bold
    //
    class Func_Bold : public Function {
    public:
        Func_Bold(void) : Function("bold") { }
        ~Func_Bold() { }

        bool Execute(class SymbolTable *symtab, class Stack *stack);
    }; // class Func_Bold
    
    //---------------------------------------------------------------------------
    // Func_Concat
    //
    class Func_Concat : public Function {
    public:
        Func_Concat(void) : Function("concat") { }
        ~Func_Concat() { }
        
        bool Execute(class SymbolTable *symtab, class Stack *stack);
    }; // class Func_Concat
    
    //---------------------------------------------------------------------------
    // Func_False
    //
    class Func_False : public Function {
    public:
        Func_False(void) : Function("false") { }
        ~Func_False() { }
        
        bool Execute(class SymbolTable *symtab, class Stack *stack);
    }; // class Func_False
    
    //---------------------------------------------------------------------------
    // Func_Include
    //
    class Func_Include : public Function {
    public:
        Func_Include(void) : Function("include") { }
        ~Func_Include() { }
        
        bool Execute(class SymbolTable *symtab, class Stack *stack);
    }; // class Func_Include
    
    //---------------------------------------------------------------------------
    // Func_Not
    //
    class Func_Not : public Function {
    public:
        Func_Not(void) : Function("not") { }
        ~Func_Not() { }
        
        bool Execute(class SymbolTable *symtab, class Stack *stack);
    }; // class Func_Not
    
    //---------------------------------------------------------------------------
    // Func_PopStack
    //
    class Func_PopStack : public Function {
    public:
        Func_PopStack(void) : Function("}") { }
        ~Func_PopStack() { }
        
        bool Execute(class SymbolTable *symtab, class Stack *stack);
    }; // class Func_PopStack
    
    //---------------------------------------------------------------------------
    // Func_PushStack
    //
    class Func_PushStack : public Function {
    public:
        Func_PushStack(void) : Function("{") { }
        ~Func_PushStack() { }
        
        bool Execute(class SymbolTable *symtab, class Stack *stack);
    }; // class Func_PushStack

    //---------------------------------------------------------------------------
    // Func_True
    //
    class Func_True : public Function {
    public:
        Func_True(void) : Function("true") { }
        ~Func_True() { }
        
        bool Execute(class SymbolTable *symtab, class Stack *stack);
    }; // class Func_True
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_lib_nftm_Function_HPP
