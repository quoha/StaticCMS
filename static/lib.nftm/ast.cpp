#include "AST.hpp"
#include "Stream.hpp"
#include "Stack.hpp"
#include "SymbolTable.hpp"
#include "Util.hpp"
#include "Variable.hpp"
#include <cstring>
#include <ctype.h>

//---------------------------------------------------------------------------
NFTM::AST::AST(astKind kind_, const char *data_, int length) {
    kind = kind_;
    next = prev = 0;
    branchThen = branchElse = 0;
    if (data_) {
        data = NFTM::StrDup(data_, length);
    }
}

//---------------------------------------------------------------------------
NFTM::AST::~AST() {
    delete [] data;
}

//---------------------------------------------------------------------------
//
bool NFTM::AST::Execute(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (!symtab || !stack) {
        return false;
    }
    NFTM::OutputStream *log = symtab->ErrorLog();
    if (log) {
        log->Write("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    }
    
    NFTM::AST *ast = this;
    
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

    return true;
}

//---------------------------------------------------------------------------
// Parse(code)
//
NFTM::AST *NFTM::AST::Parse(const char *nextChunk) {
    AST *root       = new AST(astNOOP, 0, 0);
    AST *tail       = root;

    // enclosingIF will hold the most current IF statement. the "next"
    // pointer will be abused as the pointer to the enclosing IF statement.
    // when we pop the IF statement from this mini-stack, we will reset the
    // "next" pointer. enclosingIF will be NULL if there are no active IF
    // statements.
    //
    AST *enclosingIF = 0;

    while (*nextChunk) {
        // each loop will process zero or one blocks of text and
        // zero or one blocks of code. each block of code may
        // contain zero or more words.
        //

        const char *textStart = nextChunk;
        const char *textEnd   = std::strstr(nextChunk, "<billy");
        
        if (!textEnd) {
            textEnd = std::strchr(textStart, 0);
        }

        const char *codeStart = textEnd;
        const char *codeEnd   = *codeStart ? std::strstr(codeStart, "/>") : codeStart;

        if (*codeStart) {
            // we don't want the "<billy" in the code
            //
            codeStart += 6;
        }

        if (!codeEnd) {
            codeEnd = std::strstr(codeStart, 0);
        }
        nextChunk = *codeEnd ? codeEnd + 2 : codeEnd;
        
        // if there is text, create an AST node for it and append it to the
        // current branch of the tree.
        //
        if (textStart < textEnd) {
            AST *blockText = new AST(astTEXT, textStart, (int)(codeStart - textStart));
            blockText->prev = tail;
            tail->next      = blockText;
            tail            = blockText;
        }

        // loop through the code
        const char *s = codeStart;
        while (s < codeEnd) {
            // skip leading spaces to get to the start of the word
            //
            if (isspace(*s)) {
                while (s < codeEnd && isspace(*s)) {
                    s++;
                }
                continue;
            }

            const char *word = s;
            
            // is it quoted?
            if (*word == '"' || *word == '\'') {
                // the word lasts until the next quote followed by a space
                // note that quote-quote inside a string is considered an
                // escaped quote
                //
                char quote = *word;
                while (s < codeEnd) {
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
                while (s < codeEnd && !isspace(*s)) {
                    s++;
                }
            }

            // word points to start of word and s points to one character
            // past the end of the word
            //
            const char *endOfWord = s;

            // skip trailing spaces
            //
            while (s < codeEnd && isspace(*s)) {
                s++;
            }

            // three words - if, else, and fi - plus quoted strings
            // are special, rest is just treated as code
            //
            if (word[0] == 'i' && word[1] == 'f' && endOfWord == word + 2) {
                // when we find IF, we have to create a branch in the
                // AST. the IF node will have pointers for the THEN
                // and ELSE branches. tail will point to the branch
                // being worked.
                //
                AST *startIF = new AST(astIF, word, (int)(endOfWord - word));

                // each branch may have zero or more entries, so we
                // start by creating a dummy node for both.
                //
                startIF->branchThen       = new AST(astNOOP, 0, 0);
                startIF->branchThen->prev = startIF;

                startIF->branchElse       = new AST(astNOOP, 0, 0);
                startIF->branchElse->prev = startIF;

                // push the if onto the stack. note that we are abusing the
                // "next" pointer to make this work.
                //
                if (enclosingIF) {
                    enclosingIF->next = startIF;
                }
                enclosingIF = startIF;

                // append the IF node to the tree. make the THEN branch
                // the active branch by pointing tail to it.
                //
                tail->next = startIF;
                tail       = startIF->branchThen;

            } else if (word[0] == 'e' && word[1] == 'l' && word[2] == 's' && word[3] == 'e' && endOfWord == word + 4) {
                // when we find ELSE, first check that we have an IF that
                // can be the parent. make that IF's else branch active by
                // pointing tail to it. we don't have to create a node for
                // it because the IF logic did that already.
                //

                // get the parent IF from the stack. don't pop it because
                // the ENDIF will want it to be on the stack.
                //
                AST *startIF = enclosingIF;
                if (!startIF) {
                    // error, no matching IF statement
                }

                // make the ELSE branch active by pointing tail to it
                //
                tail = startIF->branchElse;

            } else if (word[0] == 'f' && word[1] == 'i' && endOfWord == word + 2) {
                // when we find ENDIF, check that we have a matching IF for
                // it. create an AST node and make the IF, THEN and ELSE nodes
                // point to it.

                // get the parent IF from the stack. go ahead and pop it because
                // it's no longer active.
                //
                AST *startIF = enclosingIF;
                if (!startIF) {
                    // error, no matching IF statement
                }
                enclosingIF = enclosingIF->next;

                // create the AST node for the ENDIF. make the parent IF the
                // previous entry in the tree.
                //
                AST *endIF = new AST(astNOOP, 0, 0);
                endIF->prev = startIF;

                // make the next entry in the parent IF point to the ENDIF
                //
                startIF->next = endIF;

                // go back and make the THEN branch point to the ENDIF
                //
                AST *tmp = startIF->branchThen;
                while (tmp && tmp->next) {
                    tmp = tmp->next;
                }
                if (tmp) {
                    tmp->next = endIF;
                } else {
                    startIF->branchThen = endIF;
                }

                // go back and make the ELSE branch point to the ENDIF
                //
                tmp = startIF->branchElse;
                while (tmp && tmp->next) {
                    tmp = tmp->next;
                }
                if (tmp) {
                    tmp->next = endIF;
                } else {
                    startIF->branchElse = endIF;
                }

                // tail should point to the ENDIF since we just completed
                // that block
                //
                tail = endIF;

            } else if (*word == '"' || *word == '\'') {
                // strip the quotes before pushing the text
                //
                char  quote = *word;
                char *dst = new char[endOfWord - word];
                const char *src = word + 1; // skip the leading quote
                char *tgt = dst;
                while (src < endOfWord) {
                    if (*src == quote && endOfWord == src + 1) {
                        break;
                    } else if (*src == quote && *(src+1) == quote) {
                        src++;
                    }
                    *(tgt++) = *(src++);
                }
                *tgt = 0;

                // add the text to the current branch of the tree
                //
                AST *blockText  = new AST(astTEXT, dst, (int)(std::strlen(dst)));
                blockText->prev = tail;
                tail->next      = blockText;
                tail            = blockText;

            } else {
                // add the word to the current branch of the tree
                //
                AST *blockCode  = new AST(astCODE, word, (int)(endOfWord - word));
                blockCode->prev = tail;
                tail->next      = blockCode;
                tail            = blockCode;
            }
        }
    }
    
    return root;
}