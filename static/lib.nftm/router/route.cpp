#include "local.hpp"

//============================================================================
// Route(request)
//
//    ask all controllers to handle the request. first once to accept
//    gets it. controllers are queried FIFO. if no controller accepts,
//    then return the default controller.
//
NFTM::Controller *NFTM::Router::Route(NFTM::Request *request) {

	// first match on request wins. FIFO, so start with first controller
    // added.
    //
    std::list<NFTM::Controller *>::const_iterator i   = controllers.begin();
    std::list<NFTM::Controller *>::const_iterator end = controllers.end();
    while (i != end) {
        NFTM::Controller *c = *i;
		if (c->CanHandle(request)) {
			return c;
		}
        ++i;
    }

	return defaultController;
}
