#include "../Default.hpp"

//============================================================================
// Handle(cgi, request, outputStream)
//
NFTM::Stack *NFTM::DefaultController::Handle(NFTM::SymbolTable *symtab, NFTM::Request *request, NFTM::OutputStream *os) {
    NFTM::Stack *stack = 0;

	os->Write("<!-- Controller::Handle(cgi, request, os) -- default controller -->\n");

	return stack;
}
