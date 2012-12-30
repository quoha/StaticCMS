#include "../local.hpp"

//============================================================================
// Handle(cgi, request, stack)
//
bool NFTM::PostController::Handle(NFTM::SymbolTable *symtab, NFTM::Request *request, NFTM::Stack *stack) {
    if (!symtab || !request || !stack) {
        return false;
    }

    stack->PushText("<!-- PostController::Handle(symtab, request, os)\n");
    stack->PushText(request->argv[0]);

	// load model
	NFTM::PostModel *model = new NFTM::PostModel(symtab);
    model->Pull(request);
    
	delete model;
    
    // load first template. ask me how the controller knows which template
    // to start off with.
    //
    NFTM::Template *t = new NFTM::TemplateText("<p>Site_Name is <billy site_name /></p>"
                                               "<p>Page_Title is <billy page_title /></p>"
                                               "<billy 'filename.tpl' include />");
    t->Load();
    t->Execute(symtab, stack);

    // load view
    NFTM::View *view = new NFTM::View("/tmp/", "header.tpl");
    
    view->Execute(symtab, stack);
    
    delete view;
    delete t;
    
	return stack;
}
