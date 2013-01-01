#include "PostModel.hpp"
#include "../lib.nftm/Request.hpp"
#include "../lib.nftm/Stack.hpp"
#include "../lib.nftm/SymbolTable.hpp"
#include "../lib.nftm/Util.hpp"
#include "../lib.nftm/Variable.hpp"
#include <stdio.h>
#include <cstring>
#include <ctype.h>

//============================================================================
// PostModel(symtab)
//   creates blank object
//
NFTM::PostModel::PostModel(NFTM::SymbolTable *symtab_) : Model(symtab_) {

}

//============================================================================
// ~PostModel()
//
NFTM::PostModel::~PostModel() {

}

//============================================================================
// Pull(request)
//      ~~~
//      var value
//      ~~~
//      rawText
//
bool NFTM::PostModel::Pull(NFTM::Request *request) {
    if (!symtab) {
        return false;
    }

    char *articleText  = 0;
    char *articleTitle = 0;
    char *author       = 0;
    char *modelName    = "PostModel_FlatFile";
    char *pageTitle    = 0;
    char *siteName     = "StaticCMS";
    
    // turn the request into a file path
    //
    int length = 1;
    for (int idx = 0; request->argv[idx]; idx++) {
        length += (std::strlen(request->argv[idx]) + 1);
    }
    const char *pathSeparator = "/";
    char *newPath = new char[length + 1];
    newPath[0] = 0;
    for (int idx = 0; request->argv[idx]; idx++) {
        std::strcat(newPath, request->argv[idx]);

        // need a path separator for most entries except the very
        // last one and the first one, if it is a path separator
        //
        if (request->argv[idx+1]) {
            if (idx == 0 && request->argv[idx][0] == pathSeparator[0]) {
                // already there
            } else {
                std::strcat(newPath, pathSeparator);
            }
        }
    }

    char *sourceData = LoadFile(newPath, false);
    delete [] newPath;
    
    if (sourceData) {
        char *line = sourceData;
        if (line[0] == '~' && line[1] == line[0] && line[2] == line[0] && line[3] == '\n') {
            // ~~~ is start of article data
            line += 4;
            while (*line) {
                char *text     = line;
                char *nextLine = line;
                while (*nextLine && *nextLine != '\n') {
                    nextLine++;
                }
                if (*nextLine) {
                    *(nextLine++) = 0;
                }
                line = nextLine;

                if (text[0] == '~' && text[1] == text[0] && text[2] == text[0] && text[3] == 0) {
                    // ~~~ is end of article data
                    break;
                }

                // skip whitespace
                //
                char *name = text;
                while (*name && isspace(*name)) {
                    *(name++) = 0;
                }
                char *value = name;
                while (*value && !isspace(*value)) {
                    *(value++) = 0;
                }

                if (*name) {
                    if (std::strcmp(name, "title") == 0) {
                        articleTitle = value;
                        if (!pageTitle) {
                            pageTitle = articleTitle;
                        }
                    } else if (std::strcmp(name, "author") == 0) {
                        author = value;
                    } else if (std::strcmp(name, "page_title") == 0) {
                        pageTitle = value;
                    } else {
                        symtab->Add(new NFTM::VarText(name, value));
                    }
                }
            }
            articleText = line;
        }
    }

    symtab->Add(new NFTM::VarText("article_title", articleTitle));
    symtab->Add(new NFTM::VarText("article_text" , articleText));
    symtab->Add(new NFTM::VarText("author"       , author));
    symtab->Add(new NFTM::VarText("page_title"   , pageTitle));
    symtab->Add(new NFTM::VarText("//model_name" , modelName));
    symtab->Add(new NFTM::VarText("site_name"    , siteName));
    
    delete [] sourceData;
    
	return true;
}
