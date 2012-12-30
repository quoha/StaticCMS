#include "local.hpp"

//============================================================================
//
void NFTM::Variable::ClearValues(void) {
    switch (kind) {
        case vtFUNCTION:
            break;
        case vtNULL:
            break;
        case vtNUMBER:
            delete val.number;
            break;
        case vtSTACK:
            delete val.stack;
            break;
        case vtTEXT:
            delete val.text;
            break;
        case vtOTHER:
            break;
    }
    val.null  = 0;
    isNull    = true;
    isTainted = false;
    kind      = vtNULL;
}

