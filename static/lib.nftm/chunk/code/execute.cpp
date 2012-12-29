#include "local.hpp"

//============================================================================
// Execute(stack)
//
NFTM::Stack *NFTM::CodeChunk::Execute(NFTM::Stack *stack) {
    if (stack) {
        stack->Push(new NFTM::Variable("code", "***need to implement CodeChunk::Execute()"));

        // iterate through all of the words in the chunk
        //
        std::vector<char *>::iterator i;
        for (i = words.begin(); i != words.end(); ++i) {
            // execute the chunk
            //
            stack->Push(new NFTM::Variable("word", *i));
        }
    }

    return stack;
}
