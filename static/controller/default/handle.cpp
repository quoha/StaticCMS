#include "../Default.hpp"

//============================================================================
// Handle(cgi, request, outputStream)
//
bool NFTM::DefaultController::Handle(NFTM::CGI *cgi, NFTM::Request *request, NFTM::OutputStream *os) {
	os->Write("<!-- Controller::Handle(cgi, request, os) -- default controller -->\n");

	return true;
}
