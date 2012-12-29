#include "local.hpp"
#include "../Util.hpp"

//============================================================================
// Chunk(text)
//
NFTM::Chunk::Chunk(char *text_, int length) {
    text = NFTM::StrDup(text_, length);
}
