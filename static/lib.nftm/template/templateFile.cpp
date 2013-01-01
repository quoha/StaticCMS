#include "../Template.hpp"
#include "../AST.hpp"
#include "../Util.hpp"

#include <stdio.h>
#include <sys/stat.h>

//---------------------------------------------------------------------------
// TemplateFile
//
NFTM::TemplateFile::TemplateFile(const char *source_) : Template() {
    source = NFTM::StrDup(source_);
}

//---------------------------------------------------------------------------
// ~TemplateFile
//
NFTM::TemplateFile::~TemplateFile() {
    delete [] source;
}

//---------------------------------------------------------------------------
// Load()
//
NFTM::AST *NFTM::TemplateFile::Load(void) {
    delete [] data;
    data = LoadFile(source, true);

    NFTM::AST *ast = AST::Parse(data);

    delete [] data;
    data = 0;
    
    return ast;
}
