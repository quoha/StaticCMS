#include "../Template.hpp"
#include "../Stack.hpp"
#include "../SymbolTable.hpp"
#include "../Util.hpp"
#include <cstring>
#include <ctype.h>

//---------------------------------------------------------------------------
// Execute(symtab, stack)
//
bool NFTM::Template::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (!symtab || !stack || !data || !*data) {
        return false;
    }

    stack->PushFormatted("\n\n%s\n\n", data);

    char *nextChunk = data;

    while (*nextChunk) {
        char *textStart = nextChunk;
        char *codeStart = std::strstr(nextChunk, "<billy");

        if (!codeStart) {
            codeStart = std::strchr(nextChunk, 0);
        } else {
            // we don't want "<billy" in the code
            //
            *(codeStart++) = 0;
            *(codeStart++) = 0;
            *(codeStart++) = 0;
            *(codeStart++) = 0;
            *(codeStart++) = 0;
            *(codeStart++) = 0;
        }

        char *codeEnd = *codeStart ? std::strstr(codeStart, "/>") : codeStart;
        if (!codeEnd) {
            codeEnd = std::strstr(codeStart, 0);
        }

        nextChunk = *codeEnd ? codeEnd + 2 : codeEnd;

        // if there is text, push it to stack
        //
        if (*textStart) {
            stack->PushText(NFTM::StrDup(textStart));
        }

        // nil-terminate the code so that we can treat it
        // like a simple string
        //
        *codeEnd = 0;

        // loop through the code
        char *s  = codeStart;
        while (*s) {
            // skip leading spaces to get to the word
            //
            while (*s && isspace(*s)) {
                *(s++) = 0;
            }

            char *word = s;

            // the word lasts until the next whitespace
            //
            while (*s && !isspace(*s)) {
                s++;
            }

            // nil-terminate the word
            //
            while (*s && isspace(*s)) {
                *(s++) = 0;
            }

            if (*word) {
                // lookup the word in the symbol table
                NFTM::Variable *v = symtab->Lookup(word);
                if (v) {
                    stack->PushVarReference(v);
                } else if (*word == '"' || *word == '\'') {
                    stack->PushFormatted("\n>>> %s <<<\n", word);
                } else {
                    // should raise error here
                    return false;
                }
            }
        }
    }

    return true;
}
