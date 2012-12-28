#include "../local.hpp"

#include <cstring>

//============================================================================
// OutputStream(fileName)
//
NFTM::OutputStream::OutputStream(const char *fileName) {
	data   = 0;
	errmsg = 0;
	Open(fileName);
}
