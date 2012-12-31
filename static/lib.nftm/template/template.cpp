#include "../Template.hpp"
#include "../AST.hpp"
#include "../Stack.hpp"
#include "../Stream.hpp"
#include "../SymbolTable.hpp"
#include "../Util.hpp"
#include "../Variable.hpp"
#include <cstring>
#include <ctype.h>
//#include <stdio.h>

#if 0
//---------------------------------------------------------------------------
// Execute(symtab, stack)
//
bool NFTM::Template::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (!symtab || !stack || !data || !*data) {
        return false;
    }

    NFTM::AST *astRoot = AST::Parse(data);
    NFTM::AST *ast     = astRoot;

    while (ast) {
        //printf("ast.data is %d %s\n", ast->kind, ast->data);

        if (ast->kind == astNOOP) {
            ast = ast->next;
            continue;
        }

        if (ast->kind == astTEXT) {
            stack->PushText(NFTM::StrDup(ast->data));
            ast = ast->next;
            continue;
        }

        if (ast->kind == astCODE) {
            // lookup the word in the symbol table
            NFTM::Variable *v = symtab->Lookup(ast->data);
            if (v) {
                if (!v->IsFunction()) {
                    stack->PushVarReference(v);
                } else {
                    if (!v->Execute(symtab, stack)) {
                        NFTM::OutputStream *errlog = symtab->ErrorLog();
                        if (errlog) {
                            errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                            errlog->Write("\tfailed to execute word '%s'\n", ast->data);
                        }
                        return false;
                    }
                }
            } else {
                NFTM::OutputStream *errlog = symtab->ErrorLog();
                if (errlog) {
                    errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                    errlog->Write("\tclueless on how to execute '%s'\n", ast->data);
                }
                return false;
            }
            ast = ast->next;
            continue;
        }

        ast = ast->next;
    }
#if 0
    char *nextChunk = (ifLevel == 0) ? data : block;
    
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
            //
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
            
            // three special words - if, else, and fi - change the state of
            // the interpreter.
            //
            if (word[0] == 'i' && word[1] == 'f' && word[2] == 0) {
                ifLevel++;
                if (ifLevel > 30) {
                    NFTM::OutputStream *errlog = symtab->ErrorLog();
                    if (errlog) {
                        errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                        errlog->Write("\tsadly, we have a hard-limit on nested 'if' statements\n");
                    }
                    return false;
                }
            } else if (word[0] == 'f' && word[1] == 'i' && word[2] == 0) {
                ifLevel--;
                if (ifLevel < 1) {
                    NFTM::OutputStream *errlog = symtab->ErrorLog();
                    if (errlog) {
                        errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                        errlog->Write("\tfound unmatched 'fi'\n");
                    }
                    return false;
                }
            } else if (std::strcmp(word, "else") == 0) {

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
#endif

    return true;
}
#endif
