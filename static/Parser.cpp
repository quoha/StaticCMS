/**************************************************************************
 *
 * Copyright (c) 2013 Michael D Henderson
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
 * OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************
 * This file is part of StaticCMS (http://github.com/quoha/StaticCMS).
 *************************************************************************/

#include "Parser.h"
#include <stdio.h>
#include <cstring>
#include <ctype.h>


StaticCMS::Parser::Parser(void) {
    //
}

StaticCMS::Parser::~Parser() {
    //
}

StaticCMS::AST *StaticCMS::Parser::Parse(const char *sourceName, const char *data) {
    StaticCMS::AST *root = 0;
    return root;
}


//============================================================================
// from the lexer's perspective
//    view := (text | ("<cms" text "/>)*
//
// from the parser's perspective
//
//    view := code*
//    code := text | quotedText | word | if
//    if   := IF word* ( ELSE word* )? ENDIF
//


StaticCMS::Parser_Blog::Parser_Blog(void) {
    //
}


StaticCMS::Parser_Blog::~Parser_Blog() {
    //
}

//============================================================================
//
//    view := word* END_OF_INPUT
//    word := TEXT | WORD | if
//    if   := IF word* ( ELSE word* )? ENDIF
//
StaticCMS::AST *StaticCMS::Parser_Blog::Parse(const char *sourceName, const char *data) {
    printf("parse:\tentered\n");
    PState ps;
    ps.lf   = new Lexer(sourceName, data);
    ps.root = 0;
    ps.tail = 0;
    
    // prime the pump
    ps.lf->Next();
    
    // parse the input
    //
    while (!ps.lf->IsEOF()) {
        if (!ParseWord(&ps)) {
            // error - unexpected token
            break;
        }
    }
    
    if (!ps.lf->IsEOF()) {
        // error - did not parse to end of input
        //
        return 0;
    }
    
    delete ps.lf;

    printf("parse:\texiting\n");
    
    return ps.root;
}


//============================================================================
//
//    if   := IF word* ( ELSE word* )? ENDIF
//
bool StaticCMS::Parser_Blog::ParseIf(PState *ps) {
    Lexeme *lIF = ps->lf->Pop();
    Lexeme *l   = ps->lf->Peek();
    
    // process the optional then branch
    //
    while (!l->IsELSE() && !l->IsENDIF() && !l->IsEOF()) {
        if (l->IsIF()) {
            if (!ParseIf(ps)) {
                return false;
            }
        } else if (!ParseWord(ps)) {
            return false;
        }
        l = ps->lf->Peek();
    }
    
    // process the optional else branch
    //
    if (l->IsELSE()) {
        Lexeme *lELSE = ps->lf->Pop();
        
        while (!l->IsENDIF() && !l->IsEOF()) {
            if (l->IsIF()) {
                if (!ParseIf(ps)) {
                    return false;
                }
            } else if (!ParseWord(ps)) {
                return false;
            }
            l = ps->lf->Peek();
        }
    }
    
    // process the mandatory endif
    //
    Lexeme *lENDIF = ps->lf->Pop();
    if (!lENDIF->IsENDIF()) {
        // error - expected ENDIF
        //
        return false;
    }
    
    return true;
}


//============================================================================
//
//    text := text | quotedText
//
bool StaticCMS::Parser_Blog::ParseText(PState *ps) {
    Lexeme *l = ps->lf->Pop();
    
    if (l->IsText()) {
        return true;
    }
    
    if (l->IsQuotedText()) {
        return true;
    }
    
    // error - expected text, found something else
    //
    return false;
}


//============================================================================
//
//    word := TEXT | WORD | if
//
bool StaticCMS::Parser_Blog::ParseWord(PState *ps) {
    Lexeme *l = ps->lf->Peek();
    
    if (l->IsText()) {
        ps->lf->Pop();
        return true;
    }
    
    if (l->IsWord()) {
        ps->lf->Pop();
        return true;
    }
    
    if (l->IsIF()) {
        return ParseIf(ps);
    }
    
    // error - unexpected token
    //
    return false;
}


//============================================================================
//
StaticCMS::Parser_Blog::Lexer::Lexer(const char *src_, const char *data_) {
    isText = true;
    line   = 1;
    src    = src_  ? src_  : "";
    data   = data_ ? data_ : "";
    curr   = 0;
    peek   = 0;
}


//============================================================================
//
StaticCMS::Parser_Blog::Lexer::~Lexer() {
    // nothing to destroy
}


//============================================================================
//


//============================================================================
//


//============================================================================
//


//============================================================================
//


//============================================================================
//


//============================================================================
//
StaticCMS::Parser_Blog::Lexeme *StaticCMS::Parser_Blog::Lexer::Text(void) {
    Lexeme *l = new Lexeme();
    
    if (!*data) {
        l->Set(lxEOF, line, data, 0);
        return l;
    }
    
    // gather all characters up to the start of code
    //
    int         textLine  = line;
    const char *textStart = data;
    
    while (*data && std::strncmp(data, "<cms", 4) != 0) {
        if (*data == '\n') {
            line++;
        }
        data++;
    }
    
    l->Set(lxText, textLine, textStart, (int)(data - textStart));
    
    isText = false;
    data  += 4;
    
    return l;
}


//============================================================================
//
StaticCMS::Parser_Blog::Lexeme *StaticCMS::Parser_Blog::Lexer::Word(void) {
    Lexeme *l = new Lexeme();
    
    // words ignore whitespace
    //
    while (*data && isspace(*data)) {
        if (*data == '\n') {
            line++;
        }
        data++;
    }
    
    if (!*data) {
        l->Set(lxEOF, line, data, 0);
        return l;
    }
    
    if (std::strncmp(data, "/>", 2)) {
        // switch to text mode
        //
        isText = true;
        data   += 2;
        return Text();
    }
    
    const char *startWord = data;
    
    while (*data && !isspace(*data) && std::strncmp(data, "/>", 2) != 0) {
        data++;
    }
    
    l->Set(lxWord, line, startWord, (int)(data - startWord));
    
    return l;
}

//============================================================================
//
StaticCMS::Parser_Blog::Lexeme::Lexeme(void) {
    kind = lxUnknown;
    line = 0;
    data = 0;
}


//============================================================================
//
StaticCMS::Parser_Blog::Lexeme::~Lexeme() {
    delete [] data;
}


//============================================================================
//
void StaticCMS::Parser_Blog::Lexeme::Data(const char *src, int length) {
    delete [] data;
    data = new char[length + 1];
    if (src) {
        memcpy(data, src, length);
    } else {
        memset(data, 0, length);
    }
    data[length] = 0;
}


//============================================================================
//
const char *StaticCMS::Parser_Blog::Lexeme::Data(void) const {
    return data ? data : "";
}


//============================================================================
//
StaticCMS::Parser_Blog::lxKind StaticCMS::Parser_Blog::Lexeme::Kind(void) const {
    return kind;
}


//============================================================================
//
void StaticCMS::Parser_Blog::Lexeme::Kind(lxKind kind_) {
    kind = kind_;
}


//============================================================================
//
int StaticCMS::Parser_Blog::Lexeme::Line(void) const {
    return line;
}


//============================================================================
//
void StaticCMS::Parser_Blog::Lexeme::Line(int line_) {
    line = line_;
}


//============================================================================
//
void StaticCMS::Parser_Blog::Lexeme::Set(lxKind kind_, int line_, const char *src_, int length) {
    Data(src_, length);
    Kind(kind_);
    Line(line_);
}
