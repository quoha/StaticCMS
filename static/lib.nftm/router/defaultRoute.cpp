#include "local.hpp"

//============================================================================
// DefaultRoute()
//
NFTM::Controller *NFTM::Router::DefaultRoute(void) {
	return defaultController;
}

//============================================================================
// DefaultRoute(controller)
//
void NFTM::Router::DefaultRoute(NFTM::Controller *controller) {
	defaultController = controller;
}
