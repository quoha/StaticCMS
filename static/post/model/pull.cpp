#include "../local.hpp"

//============================================================================
// Pull(request)
//    dummy for development. adds a couple text variables to the symbol table.
//
bool NFTM::PostModel::Pull(NFTM::Request *request) {
    if (!symtab) {
        return false;
    }

    symtab->Add(new NFTM::Variable("site_name", "StaticCMS"));
    symtab->Add(new NFTM::Variable("page_title", "Hello, World!"));

	return true;
}
