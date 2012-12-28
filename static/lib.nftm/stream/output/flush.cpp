#include "../local.hpp"

//============================================================================
// Flush()
//
bool NFTM::OutputStream::Flush(void) {
	if (data) {
		fflush((FILE *)data);
	}

	return true;
}
