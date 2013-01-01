#include "PostModel.hpp"
#include "../lib.nftm/Request.hpp"
#include "../lib.nftm/Stack.hpp"
#include "../lib.nftm/SymbolTable.hpp"
#include "../lib.nftm/Variable.hpp"
#include <stdio.h>
#include <cstring>

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
//      <posting
//        var value
//      />
//      rawText<endSlug />rawText
//
bool NFTM::PostModel::Pull(NFTM::Request *request) {
    if (!symtab) {
        return false;
    }

    // default some values
    //
    symtab->Add(new NFTM::VarText("//model_name", "PostModel_FlatFile"));
    symtab->Add(new NFTM::VarText("site_name"   , "StaticCMS"));
    symtab->Add(new NFTM::VarText("page_title"  , "Hello, World!"));

    // turn the request into a file path
    //
    int length = 1;
    for (int idx = 0; request->argv[idx]; idx++) {
        length += (std::strlen(request->argv[idx]) + 1);
    }
    const char *pathSeparator = "/";
    char newPath[length];
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
    
    // add two articles
    NFTM::Stack *result = new NFTM::Stack;
    symtab->Add(new NFTM::VarStack("recent_posts", result));
    
    //  article id 2
    //          publish date "today"
    //          title "Article 2"
    NFTM::Stack *row;
    row = new NFTM::Stack;
    row->PushText("2");
    row->PushText("today");
    row->PushText("Article 2");
    result->PushStack(row);
    
    //  article id 7
    //          publish date "2012/10/13"
    //          title "Halloween Madness"
    row = new NFTM::Stack;
    row->PushText("7");
    row->PushText("2012/10/13");
    row->PushText("Halloween Madness");
    result->PushStack(row);
    
	return true;
}
