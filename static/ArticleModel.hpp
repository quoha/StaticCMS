#ifndef   NFTM_static_src_bin_static_ArticleModel_HPP
#define   NFTM_static_src_bin_static_ArticleModel_HPP

#include "lib.nftm/Model.hpp"

namespace NFTM {
    
    //
    // ArticleModel
    //
    class ArticleModel : public Model {
    public:
        ArticleModel(class SymbolTable *symtab) : Model(symtab) {}
        ~ArticleModel() {}

        bool Pull(void);
    }; // class ArticleModel
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_ArticleModel_HPP
