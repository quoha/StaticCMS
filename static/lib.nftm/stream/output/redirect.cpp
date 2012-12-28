#include "../local.hpp"

//============================================================================
// Redirect(fileName)
//
bool NFTM::OutputStream::Redirect(const char *fileName) {
	if (data) {
		Close();
	}
	Open(fileName);
    return true;
}
