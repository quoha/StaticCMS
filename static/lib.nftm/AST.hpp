#ifndef   NFTM_static_src_bin_static_lib_nftm_AST_HPP
#define   NFTM_static_src_bin_static_lib_nftm_AST_HPP

namespace NFTM {
    //---------------------------------------------------------------------------
    //
    enum astKind { astNOOP, astTEXT, astCODE, astIF, astENDIF };

    //---------------------------------------------------------------------------
    class AST {
    public:
        
        astKind kind;
        AST    *branchElse;
        AST    *branchThen;
        AST    *next;
        AST    *prev;
        char   *data;
        class  Function *function;
        class  Text     *text;
        class  Variable *variable;

        AST(astKind kind, const char *data, int length);
        ~AST();

        virtual bool Execute(class SymbolTable *symtab, class Stack *stack);

        static AST *Parse(class Text *code, class OutputStream *os);
    }; // class AST
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_lib_nftm_AST_HPP
