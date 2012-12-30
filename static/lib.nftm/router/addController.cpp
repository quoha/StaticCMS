#include "../Controller.hpp"
#include "../Router.hpp"

bool NFTM::Router::AddController(NFTM::Controller *controller) {
    controllers.push_back(controller);
    return true;
}