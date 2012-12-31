#include "../Template.hpp"
#include "../AST.hpp"
#include "../Util.hpp"

//---------------------------------------------------------------------------
// TemplateText
//
NFTM::TemplateText::TemplateText(const char *text_) : Template() {
    text = NFTM::StrDup(text_);
}

//---------------------------------------------------------------------------
// ~TemplateText
//
NFTM::TemplateText::~TemplateText() {
    delete [] text;
}

//---------------------------------------------------------------------------
// Load()
//
NFTM::AST *NFTM::TemplateText::Load(void) {
    return AST::Parse(text);
}
