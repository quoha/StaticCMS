#include "../local.hpp"
#include "../../lib.nftm/AST.hpp"
#include "../../lib.nftm/Model.hpp"
#include "../../lib.nftm/Template.hpp"

//============================================================================
// Handle(cgi, request, stack)
//
bool NFTM::PostController::Handle(NFTM::SymbolTable *symtab, NFTM::Request *request, NFTM::Stack *stack) {
    if (!symtab || !request || !stack) {
        return false;
    }

    //stack->PushText("<!-- PostController::Handle(symtab, request, os)\n");
    //stack->PushFormatted("request->argv[0] is '%s'\n", request->argv[0]);

	// load model
	NFTM::PostModel *model = new NFTM::PostModel(symtab);
    model->Pull(request);
    
	delete model;
    
    // first template. ask me how the controller knows which template
    // to start off with.
    //
    NFTM::Template *t = new NFTM::TemplateText("<billy '/Users/mdhender/Software/xcode/static/static/static/data/templates/footer.tpl' include />");

    // load and execute the template
    //
    bool wasSuccessful = false;
    NFTM::AST *ast = t->Load();
    if (ast) {
        wasSuccessful = ast->Execute(symtab, stack);
    }
    delete t;
    delete ast;

	return wasSuccessful;
}
