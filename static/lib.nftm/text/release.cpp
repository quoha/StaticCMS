#include "local.hpp"

//============================================================================
// Release(void)
//   resets and frees data
//
void NFTM::Text::Release(void) {

	delete [] data;

	isNull     = true;
	currLength = 0;
	maxLength  = 0;
	data       = 0;

	return;
}
