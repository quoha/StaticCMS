#include "../Default.hpp"
#include "../../lib.nftm/Variable.hpp"
#include "../../lib.nftm/Stack.hpp"

//============================================================================
// Handle(cgi, request, os)
//
bool NFTM::DefaultController::Handle(NFTM::SymbolTable *symtab, NFTM::Request *request, NFTM::Stack *stack) {
    if (!symtab || !request || !stack) {
        return false;
    }

    stack->Push(new NFTM::Variable("<!-- Controller::Handle(cgi, request, os) -- default controller -->\n"));

	return stack;
}
