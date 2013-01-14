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

#ifndef __static__Parser__
#define __static__Parser__

#include "AST.h"

namespace StaticCMS {
    class Parser {
    public:
        Parser(void);
        ~Parser();

        virtual AST *Parse(const char *sourceName, const char *data);
    }; // class Parser

    class Parser_Blog {
    public:
        Parser_Blog(void);
        ~Parser_Blog();
        
        AST *Parse(const char *sourceName, const char *data);

    private:
        enum lxKind {lxEOF = -1, lxUnknown, lxText, lxQuotedText, lxWord, lxIf, lxElse, lxEndIf};

        class Lexeme {
        public:
            Lexeme(void);
            ~Lexeme();
            
            const char *Data(void) const;
            void        Data(const char *src, int length);
            lxKind      Kind(void) const;
            void        Kind(lxKind kind);
            int         Line(void) const;
            void        Line(int line);
            void        Set(lxKind kind, int line, const char *src_, int length);
            
            bool IsELSE(void) const { return kind == lxElse; }
            bool IsENDIF(void) const { return kind == lxEndIf; }
            bool IsEOF(void) const { return kind == lxEOF; }
            bool IsIF(void) const { return kind == lxIf; }
            bool IsQuotedText(void) const { return kind == lxQuotedText; }
            bool IsText(void) const { return kind == lxText || kind == lxQuotedText; }
            bool IsWord(void) const { return kind == lxWord; }
            
            lxKind kind;
            int    line;
            char  *data;
        };

        class LexemeFactory {
        public:
            LexemeFactory(const char *src, const char *data);
            ~LexemeFactory();
            
            Lexeme *Curr(void) {
                return curr;
            }
            Lexeme *Next(void) {
                if (peek) {
                    curr = peek;
                    peek = 0;
                } else {
                    curr = isText ? Text() : Word();
                }
                return curr;
            }
            Lexeme *Peek(void) {
                if (!peek) {
                    peek = isText ? Text() : Word();
                }
                return peek;
            }
            Lexeme *Pop(void) {
                Lexeme *l = Curr();
                Next();
                return l;
            }
            
            bool IsEOF(void) const {
                return curr ? curr->IsEOF() : true;
            }
            
        private:
            Lexeme *Text(void);
            Lexeme *Word(void);
            
            bool        isText;
            int         line;
            const char *src;
            const char *data;
            
            Lexeme     *curr;
            Lexeme     *peek;
        };

        struct PState {
            class LexemeFactory *lf;
            StaticCMS::AST      *root;
            StaticCMS::AST      *tail;
        };

    }; // class Parser_Blog

}

#endif /* defined(__static__Parser__) */
