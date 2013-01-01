#include "PostController.hpp"
#include "PostModel.hpp"
#include "../lib.nftm/AST.hpp"
#include "../lib.nftm/Request.hpp"
#include "../lib.nftm/Template.hpp"
#include "../lib.nftm/Text.hpp"
#include <cstring>

//============================================================================
// PostController()
//   creates blank object
//
NFTM::PostController::PostController(void) {
}

//============================================================================
// ~PostController()
//
NFTM::PostController::~PostController() {
}

//============================================================================
// CanHandle(request)
//
bool NFTM::PostController::CanHandle(NFTM::Request *request) {
    return true;

    if (!request->argv[0] || std::strcmp(request->argv[0], "/") != 0) {
        // we always expect the request path to start with /
		return false;
	}
    
    if (!request->argv[1]) {
        return true;
    }
    
	if (std::strcmp(request->argv[1], "post") == 0) {
		return true;
	}
    
	return false;
}

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
    NFTM::Text *templateText = new NFTM::Text("<billy '/Users/mdhender/Software/xcode/static/static/static/data/templates/footer.tpl' include />");
    NFTM::Template *t = new NFTM::TemplateText(templateText);
    
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
