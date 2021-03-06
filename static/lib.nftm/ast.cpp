#include "AST.hpp"
#include "Function.hpp"
#include "Stream.hpp"
#include "Stack.hpp"
#include "SymbolTable.hpp"
#include "Text.hpp"
#include "Util.hpp"
#include "Variable.hpp"
#include <cstring>
#include <ctype.h>

//---------------------------------------------------------------------------
NFTM::AST::AST(astKind kind_, const char *data_, int length) {
    kind = kind_;
    next = prev = 0;
    branchThen = branchElse = 0;
    data = data_ ? NFTM::StrDup(data_, length) : 0;
    variable = 0;
    function = 0;
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

    NFTM::OutputStream *errlog = symtab->ErrorLog();
    //if (errlog) {
    //    errlog->Write("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    //}
    
    NFTM::AST *ast = this;
    
    while (ast) {
        //if (errlog) {
        //    errlog->Write("ast->kind is %d %s\n", ast->kind, ast->data ? ast->data : "(((null)))");
        //}
        
        if (ast->kind == astNOOP) {
            ast = ast->next;
            continue;
        }
        
        if (ast->kind == astTEXT) {
            stack->PushText(new NFTM::Text(ast->data));
            ast = ast->next;
            continue;
        }
        
        if (ast->kind == astCODE) {
            // lookup the word in the symbol table. it will be one of these:
            //   function
            //   variable
            //   text
            //   missing
            //
            if (!ast->variable && !ast->function && !ast->text) {
                NFTM::SymbolTableEntry *entry = symtab->Lookup(ast->data);
                if (entry && entry->kind == steFunction) {
                    ast->function = entry->u.function;
                }
                if (entry && entry->kind == steText) {
                    ast->text = entry->u.text;
                }
                if (entry && entry->kind == steVariable) {
                    ast->variable = entry->u.variable;
                }
            }

            // use the results of the lookup to execute the word
            //
            if (ast->function) {
                // execute the function. it will push its results onto the stack
                //
                //if (errlog) {
                //    errlog->Write("ast->function is %s\n", ast->data);
                //}

                if (!ast->function->Execute(symtab, stack)) {
                    if (errlog) {
                        errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                        errlog->Write("\tfailed to execute word '%s'\n", ast->data);
                    }
                    return false;
                }
            } else if (ast->text) {
                stack->PushText(ast->text);
            } else if (ast->variable) {
                // push a reference to the variable. this could be dangerous if a function
                // changes the value of the variable changes later.
                //
                stack->PushVarReference(ast->variable);
            } else {
                if (errlog) {
                    errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                    errlog->Write("\tword '%s' is not defined - %d\n", ast->data, ast->kind);
                }
                return false;
            }
            ast = ast->next;
            continue;
        }

        if (ast->kind == astIF) {
            // look at the top value on the stack
            bool condition = true;

            // force the top value on the stack to be a boolean
            NFTM::StackItem *item = stack->Pop();
            if (!item) {
                if (errlog) {
                    errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                    errlog->Write("\tif requires a condition on the stack\n", ast->data);
                }
                return false;
            }
            switch (item->kind) {
                case siBoolean:
                    condition = item->u.boolean;
                    break;
                case siFunction:
                    condition = true;
                    break;
                case siStack:
                    condition = true;
                    break;
                case siStackMarker:
                    if (errlog) {
                        errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                        errlog->Write("\tif will not treat stack marker as a conditional\n");
                    }
                    return false;
                case siText:
                    condition = item->u.text ? true : false;
                    break;
                case siVariable:
                    if (item->u.variable->IsNull()) {
                        condition = false;
                    } else if (item->u.variable->IsBoolean()) {
                        condition = item->u.variable->u.boolean;
                    } else {
                        condition = true;
                    }
                    break;
                default:
                    if (errlog) {
                        errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
                        errlog->Write("\tinternal error - if can't handle %d\n", item->kind);
                    }
                    return false;
            }

            // if it is true, take the THEN branch otherwise, follow ELSE branch
            //
            ast = condition ? ast->branchThen : ast->branchElse;

            continue;
        }

        if (errlog) {
            errlog->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
            errlog->Write("\tinternal error - fell through execute loop\n");
            errlog->Write("\tast->kind is %d\n\n", ast->kind);
        }
        return false;
    }

    return true;
}

//---------------------------------------------------------------------------
// Parse(code)
//
NFTM::AST *NFTM::AST::Parse(NFTM::Text *code, NFTM::OutputStream *os) {
    AST *root       = new AST(astNOOP, 0, 0);
    AST *tail       = root;

    const char *nextChunk = code ? code->text : "";
    nextChunk = nextChunk ? nextChunk : "";

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
            AST *blockText = new AST(astTEXT, textStart, (int)(textEnd - textStart));
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