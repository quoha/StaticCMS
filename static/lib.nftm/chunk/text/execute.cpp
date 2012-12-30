#include "local.hpp"

//============================================================================
// Execute(stack)
//
NFTM::Stack *NFTM::TextChunk::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        stack->PushVarReference(new NFTM::Variable("text", text));
    }
    return stack;
}
