#include "local.hpp"

//============================================================================
// Execute(stack)
//
NFTM::Stack *NFTM::CodeChunk::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (stack) {
        // iterate through all of the words in the chunk
        //
        std::vector<char *>::iterator i;
        for (i = words.begin(); i != words.end(); ++i) {
            char *word = *i;

            if (*word == '\'' || *word == '"') {
                // straight text
                stack->Push(new NFTM::Variable("~text", word + 1));
                continue;
            }

            // lookup the word in the symbol table
            NFTM::Variable *v = symtab->Lookup(word);

            // if found, execute it
            if (v) {
                if (v->IsText()) {
                    stack->Push(v);
                } else if (v->IsFunction()) {
                    v->AsFunction()->Execute(symtab, stack);
                } else {
                    // raise an error
                    stack->Push(new NFTM::Variable("~error", "CodeChunk does not know how to handle "));
                    stack->Push(new NFTM::Variable("~kind", v->Kind()));
                }
                continue;
            }

            // raise an error
            stack->Push(new NFTM::Variable("~error", "did not find "));
            stack->Push(new NFTM::Variable("~word", word));
        }
    }

    return stack;
}
