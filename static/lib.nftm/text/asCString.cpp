#include "local.hpp"

//============================================================================
// AsCString()
//   returns c-string
//
const char *NFTM::Text::AsCString(void) const {
	return (isNull || data == 0) ? "" : data;
}
