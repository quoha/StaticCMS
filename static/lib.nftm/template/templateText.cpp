#include "../Template.hpp"
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
bool NFTM::TemplateText::Load(void) {
    delete [] data;
    data = text;
    text = 0;
    
    return data ? true : false;
}
