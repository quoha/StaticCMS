#include "../Template.hpp"
#include "../Stack.hpp"
#include "../Stream.hpp"
#include "../SymbolTable.hpp"
#include "../Util.hpp"
#include "../Variable.hpp"
#include <cstring>
#include <ctype.h>

//---------------------------------------------------------------------------
// Execute(symtab, stack)
//
bool NFTM::Template::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (!symtab || !stack || !data || !*data) {
        return false;
    }

    //stack->PushFormatted("\n\n%s\n\n", data);

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

            // is it quoted?
            if (*word == '"' || *word == '\'') {
                // the word lasts until the next quote followed by a space
                // note that quote-quote inside a string is considered an
                // escaped quote
                //
                char quote = *word;
                while (*s) {
                    if (*s == quote && *(s+1) == quote) {
                        s += 2;
                        continue;
                    }
                    if (*s == quote && (*(s+1) == 0 || isspace(*(s+1)))) {
                        s++;
                        break;
                    }
                    s++;
                }
            } else {
                // the word lasts until the next whitespace
                //
                while (*s && !isspace(*s)) {
                    s++;
                }
            }

            // word must be nil-terminated for the push functions to
            // work properly.
            //
            while (*s && isspace(*s)) {
                *(s++) = 0;
            }

            if (*word) {
                // lookup the word in the symbol table
                NFTM::Variable *v = symtab->Lookup(word);
                if (v) {
                    if (!v->IsFunction()) {
                        stack->PushVarReference(v);
                    } else {
                        if (!v->Execute(symtab, stack)) {
                            NFTM::OutputStream *errlog = symtab->ErrorLog();
                            if (errlog) {
                                errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                                errlog->Write("\tfailed to execute word '%s'\n", word);
                            }
                            return false;
                        }
                    }
                } else if (*word == '"' || *word == '\'') {
                    // strip the quotes before pushing the text
                    //
                    char  quote = *word;
                    char *dst = NFTM::StrDup(word);
                    char *src = word + 1; // skip the leading quote
                    char *tgt = dst;
                    while (*src) {
                        if (*src == quote && *(src+1) == 0) {
                            break;
                        } else if (*src == quote && *(src+1) == quote) {
                            src++;
                        }
                        *(tgt++) = *(src++);
                    }
                    *tgt = 0;
                    stack->PushText(dst);
                } else {
                    NFTM::OutputStream *errlog = symtab->ErrorLog();
                    if (errlog) {
                        errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                        errlog->Write("\tclueless on how to execute '%s'\n", word);
                    }
                    return false;
                }
            }
        }
    }

    return true;
}
