#include "Template.hpp"
#include "AST.hpp"
#include "Text.hpp"
#include "Util.hpp"

//---------------------------------------------------------------------------
//
NFTM::Template::Template(void) {
    data = 0;
}

//---------------------------------------------------------------------------
//
NFTM::Template::~Template() {
    delete data;
}


//---------------------------------------------------------------------------
// TemplateFile
//
NFTM::TemplateFile::TemplateFile(NFTM::Text *fileName_) : Template() {
    fileName = new NFTM::Text(fileName_);
}

//---------------------------------------------------------------------------
// ~TemplateFile
//
NFTM::TemplateFile::~TemplateFile() {
    delete fileName;
}

//---------------------------------------------------------------------------
// Load()
//
NFTM::AST *NFTM::TemplateFile::Load(void) {
    delete [] data;
    data = new NFTM::Text(fileName, true, true);
    
    NFTM::AST *ast = AST::Parse(data);
    
    delete [] data;
    data = 0;
    
    return ast;
}

//---------------------------------------------------------------------------
// TemplateText
//
NFTM::TemplateText::TemplateText(NFTM::Text *text_) : Template() {
    text = new NFTM::Text(text_);
}

//---------------------------------------------------------------------------
// ~TemplateText
//
NFTM::TemplateText::~TemplateText() {
    delete text;
}

//---------------------------------------------------------------------------
// Load()
//
NFTM::AST *NFTM::TemplateText::Load(void) {
    return AST::Parse(text);
}
