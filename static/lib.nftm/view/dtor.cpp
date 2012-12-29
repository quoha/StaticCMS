#include "local.hpp"

//============================================================================
// ~View()
//
NFTM::View::~View() {
    delete name;
    delete path;
    delete file;
    delete data;
}
