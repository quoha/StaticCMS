#include "../local.hpp"

//============================================================================
// Close()
//
bool NFTM::OutputStream::Close(void) {
	if (data) {
		fflush((FILE *)data);
		if (data != stderr && data != stdout) {
			fclose((FILE *)data);
		}
	}

	data = 0;

	return true;
}
