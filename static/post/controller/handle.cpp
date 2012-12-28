#include "../local.hpp"

//============================================================================
// Handle(cgi, request, outputStream)
//
bool NFTM::PostController::Handle(NFTM::SymbolTable *symtab, NFTM::Request *request, NFTM::OutputStream *os) {
	// create the stack
	NFTM::Stack *stack = new NFTM::Stack();

	// load model
	NFTM::PostModel *model = new NFTM::PostModel(symtab);
    model->Pull(request);

	// load view
	os->Write("<!-- PostController::Handle(symtab, request, os) -- controller %s -->\n", request->argv[0]);

	delete model;

	return stack ? false : true;
}
