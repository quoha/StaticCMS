#include "local.hpp"

//============================================================================
// Execute(stack)
//
NFTM::Stack *NFTM::CodeChunk::Execute(NFTM::Stack *stack) {
    if (stack) {
        stack->Push(new NFTM::Variable("code", "***need to implement CodeChunk::Execute()"));
    }
    return stack;
}
