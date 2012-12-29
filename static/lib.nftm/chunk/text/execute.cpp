#include "local.hpp"

//============================================================================
// Execute(stack)
//
NFTM::Stack *NFTM::TextChunk::Execute(NFTM::Stack *stack) {
    if (stack) {
        stack->Push(new NFTM::Variable("text", text));
    }
    return stack;
}