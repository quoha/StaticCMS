#include "local.hpp"
#include <cstring>

//============================================================================
// ChunkFactory()
//
NFTM::Chunk *NFTM::View::ChunkFactory(void) {
    if (!text || !*text) {
        return 0;
    }

    char *startOfChunk = text;
    char *endOfChunk;

    char *startOfCode  = std::strstr(startOfChunk, "<billy");

    // code starts with "<billy". text does not.
    //
    if (startOfCode != startOfChunk) {
        endOfChunk = startOfCode;
        if (!endOfChunk) {
            endOfChunk = std::strchr(startOfChunk, 0);
        }
        text = endOfChunk;

        return new NFTM::TextChunk(startOfChunk, (int)(endOfChunk - startOfChunk));
    }

    // we don't want "<billy" in the code
    //
    startOfChunk += 6;
    
    // find the end of the code. that's either "/>" or the
    // end of the buffer
    //
    endOfChunk = startOfChunk;
    while (*endOfChunk) {
        if (endOfChunk[0] == '/' && endOfChunk[1] == '>') {
            break;
        }
        endOfChunk++;
    }
    
    // leave text pointing past the /> characters
    // but not beyond the end of the buffer
    //
    text = endOfChunk;
    if (*text) {
        text += 2;
    }
    
    return new NFTM::CodeChunk(startOfChunk, (int)(endOfChunk - startOfChunk));
}
