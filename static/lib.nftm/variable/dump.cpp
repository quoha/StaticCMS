#include "local.hpp"
#include "../Stream.hpp"
#include "../Util.hpp"

//---------------------------------------------------------------------------
//
void NFTM::Variable::Dump(NFTM::OutputStream *os) {
    if (os) {
        os->Write("\t\tvar %s is %s%s\n", Name(), IsNull() ? "null " : "", Kind());
        if (!IsNull() && IsText()) {
            char minibuf[64 + 1];
            NFTM::StrCopy(minibuf, val.text->AsCString(), 64);
            char *s = minibuf;
            while (*s && *s != '\n') {
                s++;
            }
            *s = 0;
            os->Write("\t\t\t%s\n", minibuf);
        }
    }
}