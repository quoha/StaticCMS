#include "local.hpp"

//============================================================================
//
bool NFTM::Variable::Value(void) {
    ClearValues();

    val.null  = 0;
    isNull    = true;
    isTainted = false;
    kind      = vtNULL;

    return true;
}

//============================================================================
//
bool NFTM::Variable::Value(NFTM::Function *function) {
    ClearValues();

    val.function = function;
    isNull       = val.function ? true : false;
    isTainted    = false;
    kind         = vtFUNCTION;
    
    return true;
}

//============================================================================
//
bool NFTM::Variable::Value(NFTM::Number *number) {
    ClearValues();

    val.number = number;
    isNull     = val.number ? true : false;
    isTainted  = false;
    kind       = vtNUMBER;
    
    return true;
}

//============================================================================
//
bool NFTM::Variable::Value(NFTM::Stack *stack) {
    ClearValues();

    val.stack = stack;
    isNull    = val.stack ? false : true;
    isTainted = false;
    kind      = vtSTACK;
    
    return true;
}

//============================================================================
//
bool NFTM::Variable::Value(NFTM::Text *text) {
    ClearValues();

    val.text  = text;
    isNull    = val.text ? false : true;
    isTainted = false;
    kind      = vtTEXT;
    
    return true;
}

//============================================================================
//
bool NFTM::Variable::Value(NFTM::Text *text_, int length) {
    ClearValues();

    val.text  = new NFTM::Text(text_, length);
    isNull    = val.text ? false : true;
    isTainted = false;
    kind      = vtTEXT;
    
    return true;
}

//============================================================================
//
bool NFTM::Variable::Value(const char *text_) {
    ClearValues();

    val.text  = new NFTM::Text(text_);
    isNull    = val.text ? false : true;
    isTainted = false;
    kind      = vtTEXT;
    
    return true;
}

//============================================================================
//
bool NFTM::Variable::Value(const char *text_, int length) {
    ClearValues();

    val.text  = new NFTM::Text(text_, length);
    isNull    = val.text ? false : true;
    isTainted = false;
    kind      = vtTEXT;
    
    return true;
}
