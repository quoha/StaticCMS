#ifndef   NFTM_static_src_bin_static_Router_HPP
#define   NFTM_static_src_bin_static_Router_HPP

namespace NFTM {

    //----------------------------------------------------------------------------
    // Router
    //    Routes should be added FIFO
    //
    class Router {
    public:
        Router(void);
        ~Router();
        
        bool AddRoute(const char *path, class Controller *controller);
        bool AddRoute(const char *path, const char *action, class Controller *controller);
        
        class Controller *DefaultRoute(void);
        void              DefaultRoute(class Controller *controller);
        class Controller *Route(class Request *request);
        
        class Controller *defaultController;
        
        struct Route {
            struct Route     *prev;
            struct Route     *next;
            const char       *path;
            const char       *action;
            class Controller *controller;
        } *routeTop, *routeBottom;
    }; // class Router
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_Router_HPP
