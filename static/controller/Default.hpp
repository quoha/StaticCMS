#ifndef   NFTM_static_src_bin_static_controller_Default_HPP
#define   NFTM_static_src_bin_static_controller_Default_HPP

#include "../lib.nftm/Stream.hpp"
#include "../lib.nftm/Controller.hpp"
#include "../lib.nftm/Model.hpp"

namespace NFTM {

class DefaultModel : public Model {
public:
}; // class DefaultModel

class DefaultController : public Controller {
public:
	bool CanHandle(class Request *request);
	bool Handle(class CGI *cgi, class Request *request, class OutputStream *os);
	bool View(class OutputStream *os);
}; // class DefaultController

} // namespace NFTM

#endif // NFTM_static_src_bin_static_controller_Default_HPP
