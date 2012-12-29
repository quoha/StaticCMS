#include "local.hpp"
#include "../Util.hpp"

//============================================================================
// View(templateFile)
//
NFTM::View::View(const char *templateFile) {
    name = NFTM::StrDup(templateFile);
    path = NFTM::StrDup(0);
    file = NFTM::StrDup(templateFile);
    data = 0;
    text = 0;
}

//============================================================================
// View(templatePath, templateFile)
//
NFTM::View::View(const char *templatePath, const char *templateFile) {
    name = NFTM::StrCat(templatePath, templateFile);
    path = NFTM::StrDup(templatePath);
    file = NFTM::StrDup(templateFile);
    data = 0;
    text = 0;
}
