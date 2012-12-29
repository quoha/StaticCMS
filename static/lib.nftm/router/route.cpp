#include "local.hpp"

//============================================================================
// Route(request)
//
//    ask all controllers to handle the request. first once to accept
//    gets it. controllers are queried FIFO. if no controller accepts,
//    then return the default controller.
//
NFTM::Controller *NFTM::Router::Route(NFTM::Request *request) {
	// first match on request wins. FIFO, so start at bottom
    //
    for (struct Route *route = routeBottom; route; route = route->next) {
		if (route->controller->CanHandle(request)) {
			return route->controller;
		}
	}

	return defaultController;
}
