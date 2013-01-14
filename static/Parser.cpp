#include "AST.h"
#include <cstring>
#include <ctype.h>

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


//============================================================================
//
enum lxKind {
    lxEOF = -1,
    lxUnknown,
    lxText,
    lxQuotedText,
    lxWord,
    lxIf,
    lxElse,
    lxEndIf
};


//============================================================================
//
struct PState {
    class LexemeFactory *lf;
    StaticCMS::AST           *root;
    StaticCMS::AST           *tail;
};


//============================================================================
//
StaticCMS::AST *ParseView(const char *sourceName, const char *data);
bool            ParseWord(PState *ps);
bool            ParseIf(PState *ps);
bool            ParseElse(PState *ps);

//============================================================================
//
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


//============================================================================
//
Lexeme::Lexeme(void) {
    kind = lxUnknown;
    line = 0;
    data = 0;
}


//============================================================================
//
Lexeme::~Lexeme() {
    delete [] data;
}


//============================================================================
//
void Lexeme::Data(const char *src, int length) {
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
const char *Lexeme::Data(void) const {
    return data ? data : "";
}


//============================================================================
//
lxKind Lexeme::Kind(void) const {
    return kind;
}


//============================================================================
//
void Lexeme::Kind(lxKind kind_) {
    kind = kind;
}


//============================================================================
//
int Lexeme::Line(void) const {
    return line;
}


//============================================================================
//
void Lexeme::Line(int line_) {
    line = line_;
}


//============================================================================
//
void Lexeme::Set(lxKind kind_, int line_, const char *src_, int length) {
    Data(src_, length);
    Kind(kind_);
    Line(line_);
}


//============================================================================
//
class LexemeFactory {
public:
    LexemeFactory(const char *src, const char *data);
    ~LexemeFactory();

    Lexeme *Curr(void);
    Lexeme *Next(void);
    Lexeme *Peek(void);
    Lexeme *Pop(void);

    bool IsEOF(void) const;

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


//============================================================================
//
LexemeFactory::LexemeFactory(const char *src_, const char *data_) {
    isText = true;
    line   = 1;
    src    = src_  ? src_  : "";
    data   = data_ ? data_ : "";
    curr   = 0;
    peek   = 0;
}


//============================================================================
//
LexemeFactory::~LexemeFactory() {
    // nothing to destroy
}


//============================================================================
//
Lexeme *LexemeFactory::Curr(void) {
    return curr;
}


//============================================================================
//
bool LexemeFactory::IsEOF(void) const {
    return curr ? curr->IsEOF() : true;
}


//============================================================================
//
Lexeme *LexemeFactory::Next(void) {
    if (peek) {
        curr = peek;
        peek = 0;
    } else {
        curr = isText ? Text() : Word();
    }
    return curr;
}


//============================================================================
//
Lexeme *LexemeFactory::Peek(void) {
    if (!peek) {
        peek = isText ? Text() : Word();
    }
    return peek;
}


//============================================================================
//
Lexeme *LexemeFactory::Pop(void) {
    Lexeme *l = Curr();
    Next();
    return l;
}


//============================================================================
//
Lexeme *LexemeFactory::Text(void) {
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
Lexeme *LexemeFactory::Word(void) {
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
//    view := word* END_OF_INPUT
//    word := TEXT | WORD | if
//    if   := IF word* ( ELSE word* )? ENDIF
//
StaticCMS::AST *ParseView(const char *sourceName, const char *data) {
    PState ps;
    ps.lf   = new LexemeFactory(sourceName, data);
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

    return ps.root;
}


//============================================================================
//
//    word := TEXT | WORD | if
//
bool ParseWord(PState *ps) {
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
//    if   := IF word* ( ELSE word* )? ENDIF
//
bool ParseIf(PState *ps) {
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
bool ParseText(PState *ps) {
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
