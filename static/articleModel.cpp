#include "ArticleModel.hpp"
#include "lib.nftm/SymbolTable.hpp"
#include "lib.nftm/Text.hpp"
#include "lib.nftm/Variable.hpp"

bool NFTM::ArticleModel::Pull(void) {
    NFTM::Variable *v;
    NFTM::Variable *articleTitle = 0;
    NFTM::Variable *pageTitle    = 0;

    NFTM::SymbolTableEntry *entry;
    
    entry = symtab->Lookup("articleTitle");
    if (entry && entry->kind == steVariable) {
        articleTitle = entry->u.variable;
    }
    if (!articleTitle) {
        // provide a poor one
        articleTitle = new NFTM::Variable("articleTitle", new NFTM::Text("this space for rent"));
        symtab->Add(articleTitle);
    }

    entry = symtab->Lookup("articleTitle");
    if (entry && entry->kind == steVariable) {
        pageTitle = entry->u.variable;
    }
    if (!pageTitle) {
        pageTitle = new NFTM::Variable("pageTitle", articleTitle);
        symtab->Add(pageTitle);
    }

    symtab->Add(new NFTM::Variable("//modelName", new NFTM::Text("ArticleModel")));

    return true;
}
