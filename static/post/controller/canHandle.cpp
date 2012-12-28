#include "../local.hpp"
#include <cstring>

//============================================================================
// CanHandle(request)
//
bool NFTM::PostController::CanHandle(NFTM::Request *request) {
    if (!request->argv[0] || std::strcmp(request->argv[0], "/") != 0) {
        // we always expect the request path to start with /
		return false;
	}
    
    if (!request->argv[1]) {
        return true;
    }

	if (std::strcmp(request->argv[1], "post") == 0) {
		return true;
	}

	return false;
}
