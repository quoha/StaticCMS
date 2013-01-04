#include "ArticleController.hpp"
#include "ArticleModel.hpp"
#include "lib.nftm/AST.hpp"
#include "lib.nftm/Stack.hpp"
#include "lib.nftm/Stream.hpp"
#include "lib.nftm/SymbolTable.hpp"
#include "lib.nftm/Template.hpp"
#include "lib.nftm/Text.hpp"
#include <stdio.h>

//============================================================================
// ArticleController()
//   creates blank object
//
NFTM::ArticleController::ArticleController(NFTM::Text *rootInput_) {
    rootInput    = rootInput_;
    templateFile = new NFTM::Text("template/article");
}

//============================================================================
// ~ArticleController()
//
NFTM::ArticleController::~ArticleController() {
    delete templateFile;
}

//============================================================================
// Handle(cgi, request, stack)
//
bool NFTM::ArticleController::Handle(NFTM::SymbolTable *symtab, NFTM::Stack *stack) {
    if (!symtab || !stack) {
        return false;
    }

    stack->PushFormatted("<!-- ArticleController -->\n");

    NFTM::OutputStream *errlog = symtab->ErrorLog();

	// load model into the symbol table
    //
	NFTM::ArticleModel *model = new NFTM::ArticleModel(symtab);
    model->Pull();
	delete model;

    NFTM::Template *t = new NFTM::TemplateFile(new NFTM::Text(rootInput, templateFile));

    // load and execute the template
    //
    bool wasSuccessful = false;
    NFTM::AST *ast = t->Load(errlog);
    if (!ast) {
        perror(templateFile->text);
        wasSuccessful = false;
    } else {
        wasSuccessful = ast->Execute(symtab, stack);
    }
    delete t;
    delete ast;
    
	return wasSuccessful;
}
