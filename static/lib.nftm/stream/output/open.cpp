#include "../local.hpp"

#include <errno.h>
#include <cstring>

//============================================================================
// Open(fileName)
//
bool NFTM::OutputStream::Open(const char *fileName) {
	errmsg = 0;

	if (data) {
		Close();
	}

	if (std::strcmp(fileName, "-") == 0) {
		data = stdout;
	} else if (std::strcmp(fileName, "null") == 0) {
		data = NULL;
	} else if (std::strcmp(fileName, "stderr") == 0) {
		data = stderr;
	} else if (std::strcmp(fileName, "stdout") == 0) {
		data = stdout;
	} else {
		data = fopen(fileName, "w");
		if (!data) {
			errmsg = strerror(errno);
		}
	}

	return data ? true : false;
}
