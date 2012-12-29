#ifndef   NFTM_static_src_bin_static_Function_HPP
#define   NFTM_static_src_bin_static_Function_HPP

namespace NFTM {
    
    //----------------------------------------------------------------------------
    // Function
    //   the Function class manipulates the stack.
    //
    //   it's an abstract base class, so inherit and extend, please.
    //
    //   btw, please be sure to set the name.
    //
    class Function {
    public:
        Function(class SymbolTable *symtab) { name = ""; }
        virtual ~Function() { }
        
        const char *Name(void) const {
            return name;
        }
        
        virtual class Stack *Execute(class SymbolTable *symtab, class Stack *stack) = 0;
        
        const char *name;
        
    }; // class Function

    //----------------------------------------------------------------------------
    // F_Include
    class F_Include : public Function {
    public:
        F_Include(class SymbolTable *symtab);
        ~F_Include() { }
        class Stack *Execute(class SymbolTable *symtab, class Stack *stack);
    }; // class F_Include

    bool LoadAllFunctions(class SymbolTable *symtab);
} // namespace NFTM

#endif // NFTM_static_src_bin_static_Function_HPP
