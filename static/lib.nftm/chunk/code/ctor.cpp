#include "local.hpp"
#include <ctype.h>

//============================================================================
// CodeChunk(text)
//
NFTM::CodeChunk::CodeChunk(char *text_, int length_) : Chunk(text_, length_) {
    char *s = text;
    while (*s) {
        while (isspace(*s)) {
            *(s++) = 0;
        }
        if (*s) {
            words.push_back(s);
            while (*s && !isspace(*s)) {
                s++;
            }
        }
    }
}
