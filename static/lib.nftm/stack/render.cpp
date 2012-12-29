#include "local.hpp"
#include "../Variable.hpp"
#include "../Stream.hpp"

//============================================================================
// Render(os)
//
bool NFTM::Stack::Render(NFTM::OutputStream *os) {
    if (!os) {
        return false;
    }

    while (!items.empty()) {
        Item *i = items.front();
        switch (i->kind) {
            case Item::siTaintedText:
                os->Write("%s", i->u.text);
                break;
            case Item::siText:
                os->Write("%s", i->u.text);
                break;
            case Item::siStack:
                if (!i->u.stack->Render(os)) {
                    return false;
                }
                break;
            case Item::siVarReference:
                if (!i->u.var->Render(os)) {
                    return false;
                }
                break;
        }
        delete i;
        items.pop_back();
    }

    return true;
}