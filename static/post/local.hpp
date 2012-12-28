#ifndef   NFTM_static_src_bin_static_post_local_HPP
#define   NFTM_static_src_bin_static_post_local_HPP

#include "../lib.nftm/SymbolTable.hpp"
#include "../lib.nftm/Stream.hpp"
#include "../lib.nftm/Text.hpp"
#include "../lib.nftm/Stack.hpp"
#include "../lib.nftm/Request.hpp"
#include "../lib.nftm/Controller.hpp"
#include "../lib.nftm/Model.hpp"

namespace NFTM {
    
    class PostModel : public Model {
    public:
        PostModel(class SymbolTable *symtab);
        ~PostModel();
        
        bool Push(class Stack *stack, const char *word);
    }; // class PostModel
    
    class PostController : public Controller {
    public:
        PostController(void);
        ~PostController();
        
        bool CanHandle(class Request *request);
        bool Handle(class SymbolTable *symtab, class Request *request, class OutputStream *os);
        bool View(class OutputStream *os);
    }; // class PostController
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_local_HPP
