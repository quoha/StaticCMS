#include "local.hpp"

//============================================================================
// ~Text()
//   deletes object
//
NFTM::Text::~Text() {
	delete [] data;
}
