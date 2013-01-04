#ifndef   NFTM_static_src_bin_static_ArticleController_HPP
#define   NFTM_static_src_bin_static_ArticleController_HPP

#include "lib.nftm/Controller.hpp"

namespace NFTM {
    
    class ArticleController : public Controller {
    public:
        ArticleController(class Text *text);
        ~ArticleController();

        bool Handle(class SymbolTable *symtab, class Stack *stack);

        class Text *rootInput;
        class Text *templateFile;
    }; // class ArticleController
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_ArticleController_HPP
