#include "local.hpp"
#include "../Util.hpp"

//============================================================================
// AddRoute(path, controller)
//
bool NFTM::Router::AddRoute(const char *path_, NFTM::Controller *controller) {
	return AddRoute(path_, 0, controller);
}

//============================================================================
// AddRoute(path, action, controller)
//
//    we're going to process routes FIFO, so more specific controllers
//    should be added before more general (for example, add "/post" before
//    adding "/"
//
bool NFTM::Router::AddRoute(const char *path_, const char *action_, NFTM::Controller *controller) {
	struct Route *route = new struct Route;
	route->path         = path_   ? StrDup(path_  ) : 0;
	route->action       = action_ ? StrDup(action_) : 0;
	route->controller   = controller;
    route->prev         = routeTop;
	route->next         = 0;

    if (!routeTop) {
        routeTop = routeBottom = route;
    } else {
        routeTop->next = route;
        routeTop = route;
    }
	return true;
}
