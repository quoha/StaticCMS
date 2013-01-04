#include "Template.hpp"
#include "AST.hpp"
#include "Stream.hpp"
#include "Text.hpp"
#include "Util.hpp"
#include <stdio.h>

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
NFTM::AST *NFTM::TemplateFile::Load(NFTM::OutputStream *os) {
    delete data;
    data = new NFTM::Text(fileName, true, true);
    if (!data || data->text == 0) {
        perror(fileName->text);
        if (os) {
            os->Write("\nerror:\t%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
            os->Write("\tunable to open template file for reading\n");
            os->Write("\t%-20s == '%s'\n\n", "templateFile", fileName->text);
        }
        return 0;
    }
    
    NFTM::AST *ast = AST::Parse(data, os);
    
    delete data;
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
NFTM::AST *NFTM::TemplateText::Load(NFTM::OutputStream *os) {
    return AST::Parse(text, os);
}
