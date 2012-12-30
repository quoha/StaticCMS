#include "../Variable.hpp"
#include "../SymbolTable.hpp"

//============================================================================
// LoadAllVarFunctions(symtab)
//
void NFTM::LoadAllVarFunctions(NFTM::SymbolTable *symtab) {
    if (!symtab) {
        return;
    }

    symtab->Add(new NFTM::VarFunc_Concat);
    symtab->Add(new NFTM::VarFunc_Include);
    symtab->Add(new NFTM::VarFunc_PopStack);
    symtab->Add(new NFTM::VarFunc_PushStack);
}
