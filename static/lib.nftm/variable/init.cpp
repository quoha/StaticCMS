#include "local.hpp"

//============================================================================
//
void NFTM::Variable::Init(void) {
    val.null  = 0;
    isNull    = true;
    isTainted = false;
    kind      = vtNULL;
}

