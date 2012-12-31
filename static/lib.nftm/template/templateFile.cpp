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
    data = 0;
    
    struct stat statBuf;
    if (source && *source && stat(source, &statBuf) == 0) {
        data = new char[statBuf.st_size + 1];
        
        FILE *fp = fopen(source, "r");
        if (!fp) {
            delete [] data;
            data = 0;
            return false;
        } else if (fread(data, statBuf.st_size, 1, fp) != 1) {
            delete [] data;
            data = 0;
            fclose(fp);
            return false;
        }
        
        fclose(fp);
        
        // get rid of one trailing new-line
        //
        if (statBuf.st_size > 0 && data[statBuf.st_size - 1] == '\n') {
            data[statBuf.st_size - 1] = 0;
        }

        data[statBuf.st_size] = 0;
    }

    NFTM::AST *ast = AST::Parse(data);

    delete [] data;
    data = 0;
    
    return ast;
}
