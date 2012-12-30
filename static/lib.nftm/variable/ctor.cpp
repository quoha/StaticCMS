#include "local.hpp"
#include "../Util.hpp"
#include <stdio.h>

//============================================================================
//
NFTM::Variable::Variable(const char *name_) {
    isNull    = true;
    isTainted = false;
    kind      = vtNULL;

    if (name_) {
        StrCopy(name, name_, maxNameLength);
    } else {
        sprintf(name, ".%p", this);
    }
}


