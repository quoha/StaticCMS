#ifndef   NFTM_static_src_bin_static_post_PostModel_HPP
#define   NFTM_static_src_bin_static_post_PostModel_HPP

#include "../lib.nftm/Model.hpp"

namespace NFTM {
    
    //
    // PostModel
    //   reads a flat file
    //      ~~~
    //      var value
    //      ~~~
    //      rawText
    //   sets some default values
    //      slugWords 120
    //
    class PostModel : public Model {
    public:
        PostModel(class SymbolTable *symtab);
        ~PostModel();
        
        bool Pull(class Request *request);
    }; // class PostModel
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_post_PostModel_HPP
