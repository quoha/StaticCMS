#include "../local.hpp"

//============================================================================
// Handle(cgi, request, outputStream)
//
NFTM::Stack *NFTM::PostController::Handle(NFTM::SymbolTable *symtab, NFTM::Request *request, NFTM::OutputStream *os) {
	os->Write("<!-- PostController::Handle(symtab, request, os) -- controller %s -->\n", request->argv[0]);

	// create the stack
	NFTM::Stack *stack = new NFTM::Stack();

	// load model
	NFTM::PostModel *model = new NFTM::PostModel(symtab);
    model->Pull(request);

	delete model;

    // load view
    NFTM::View *view = new NFTM::View("/tmp/", "header.tpl");

    view->Execute(symtab, stack);

    delete view;

	return stack;
}
