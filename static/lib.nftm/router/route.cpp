#include "local.hpp"

//============================================================================
// Route(request)
//
NFTM::Controller *NFTM::Router::Route(NFTM::Request *request) {
	NFTM::Controller *c = defaultController;

	// first match on request wins. LIFO, so start at top
    //
	struct Route *route = routeTop;
	while (route) {
		if (route->controller->CanHandle(request)) {
			c = route->controller;
			break;
		}
		route = route->prev;
	}

	return c;
}
