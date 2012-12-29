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

    stack->Push(new NFTM::Variable(".", "Hello, World!"));
    NFTM::Stack *st = new NFTM::Stack();
    st->Push(new NFTM::Variable("01", "aStack01"));
    st->Push(new NFTM::Variable("02", "aStack02"));
    stack->Push(new NFTM::Variable("aStack", st));

    // load view
    NFTM::View *view = new NFTM::View("/tmp/", "header.tpl");

    view->Execute(stack);

    delete view;

	return stack;
}
