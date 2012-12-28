#include "local.hpp"
#include "../Stream.hpp"

//---------------------------------------------------------------------------
//
void NFTM::Request::Dump(NFTM::OutputStream *os) {
    if (os) {
        os->Write("\t\trequest %s\n", request);
        os->Write("\t\t  query %s\n", queryString);
        os->Write("\t\t symtab %s\n", symtab ? "present" : "missing");
        for (int idx = 0; argv[idx]; idx++) {
            os->Write("\t\t    %3d '%s'\n", idx, argv[idx]);
        }
    }
}