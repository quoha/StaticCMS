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

        AST(astKind kind, const char *data, int length);
        ~AST();

        static AST *Parse(const char *code);
    }; // class AST
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_lib_nftm_AST_HPP
