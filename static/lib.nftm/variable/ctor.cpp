#include "local.hpp"
#include "../Util.hpp"
#include <stdio.h>

//============================================================================
//
NFTM::Variable::Variable(const char *name_) {
    Init();

    if (name_) {
        StrCopy(name, name_, maxNameLength);
    } else {
        sprintf(name, ".%p", this);
    }

    Value();
}

//============================================================================
//
NFTM::Variable::Variable(const char *name_, NFTM::Stack *stack) {
    Init();
    
    if (name_) {
        StrCopy(name, name_, maxNameLength);
    } else {
        sprintf(name, ".%p", this);
    }

    Value(stack);
}

//============================================================================
//
NFTM::Variable::Variable(const char *name_, NFTM::Text *text) {
    Init();
    
    if (name_) {
        StrCopy(name, name_, maxNameLength);
    } else if (text) {
        StrCopy(name, text->AsCString(), maxNameLength);
    } else {
        sprintf(name, ".%p", this);
    }

    Value(text);
}

//============================================================================
//
NFTM::Variable::Variable(const char *name_, NFTM::Text *text, int length) {
    Init();
    
    if (name_) {
        StrCopy(name, name_, maxNameLength);
    } else if (text) {
        StrCopy(name, text->AsCString(), maxNameLength);
    } else {
        sprintf(name, ".%p", this);
    }

    Value(text, length);
}

//============================================================================
//
NFTM::Variable::Variable(const char *name_, const char *text) {
    Init();

    if (name_) {
        StrCopy(name, name_, maxNameLength);
    } else if (text) {
        StrCopy(name, text, maxNameLength);
    } else {
        sprintf(name, ".%p", this);
    }

    Value(text);
}

//============================================================================
//
NFTM::Variable::Variable(const char *name_, const char *text, int length) {
    Init();
    
    if (name_) {
        StrCopy(name, name_, maxNameLength);
    } else if (text) {
        StrCopy(name, text, maxNameLength);
    } else {
        sprintf(name, ".%p", this);
    }

    Value(text, length);
}
