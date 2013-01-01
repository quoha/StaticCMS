#include "../Default.hpp"
#include "../../lib.nftm/Stack.hpp"
#include "../../lib.nftm/Text.hpp"
#include "../../lib.nftm/Variable.hpp"

//============================================================================
// Handle(cgi, request, os)
//
bool NFTM::DefaultController::Handle(NFTM::SymbolTable *symtab, NFTM::Request *request, NFTM::Stack *stack) {
    if (!symtab || !request || !stack) {
        return false;
    }

    stack->PushText(new NFTM::Text("<!-- Controller::Handle(cgi, request, os) -- default controller -->\n"));

	return true;
}
