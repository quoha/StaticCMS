#ifndef   NFTM_static_src_bin_static_post_PostController_HPP
#define   NFTM_static_src_bin_static_post_PostController_HPP

#include "../lib.nftm/Controller.hpp"

namespace NFTM {
    
    class PostController : public Controller {
    public:
        PostController(void);
        ~PostController();
        
        bool CanHandle(class Request *request);
        bool Handle(class SymbolTable *symtab, class Request *request, class Stack *stack);
    }; // class PostController
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_PostController_HPP
