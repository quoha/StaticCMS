#include "../Default.hpp"

//============================================================================
// View(outputStream)
//
bool NFTM::DefaultController::View(NFTM::OutputStream *os) {
	os->Write("<!-- set up view for controller -->\n");

	return true;
}
