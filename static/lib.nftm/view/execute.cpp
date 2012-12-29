#include "local.hpp"

//============================================================================
// Execute(stack)
//
NFTM::Stack *NFTM::View::Execute(NFTM::Stack *stack) {
    if (stack) {
        // iterate through all of the chunks in the view
        //
        std::vector<Chunk>::iterator i;
        for (i = chunks.begin(); i != chunks.end(); ++i) {
            // execute the chunk
            //
            if (!(*i).Execute(stack)) {
                return 0;
            }
        }
    }
    return stack;
}
