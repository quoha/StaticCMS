#ifndef   NFTM_static_src_bin_static_Router_HPP
#define   NFTM_static_src_bin_static_Router_HPP

#include <list>

namespace NFTM {

    //----------------------------------------------------------------------------
    // Router
    //    Routes should be added FIFO
    //
    class Router {
    public:
        Router(void);
        ~Router();

        bool AddController(class Controller *controller);
        void DefaultController(class Controller *controller);

        class Controller *Route(class Request *request);

        class Controller             *defaultController;
        std::list<class Controller *> controllers;
    }; // class Router
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_Router_HPP
