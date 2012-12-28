#include "../local.hpp"

#include <stdio.h>
#include <stdarg.h>

//============================================================================
// Write(fmt, ...)
//
bool NFTM::OutputStream::Write(const char *fmt, ...) {
	if (!data) {
		return false;
	}

	if (fmt && *fmt) {
		va_list ap;
		va_start(ap, fmt);
		vfprintf((FILE *)data, fmt, ap);
		va_end(ap);
	}

	return true;
}
