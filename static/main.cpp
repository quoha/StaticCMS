//
//  main.cpp
//  static
//
//  Created by Michael Henderson on 12/27/12.
//  Copyright (c) 2012 Michael Henderson. All rights reserved.
//

// four things per terence parr
//  1. attribute reference
//  2. conditional template inclusion
//  3. recursive template references
//  4. "map" operator

#include "local.hpp"
#include "lib.nftm/Stack.hpp"
#include "lib.nftm/SymbolTable.hpp"
#include "ArticleController.hpp"
#include <stdio.h>

#define DNL fprintf(stderr, "%s: %d\n", __FILE__, __LINE__);

int main(int argc, char *argv[]) {
	stderr = stdout;

    NFTM::Text *inputFile    = 0;
    NFTM::Text *outputFile   = 0;
    NFTM::Text *rootInput    = new NFTM::Text("./");
    NFTM::Text *rootOutput   = new NFTM::Text("./");
    NFTM::OutputStream *obuf = 0;
    NFTM::OutputStream *oerr = new NFTM::OutputStream("stderr");
    NFTM::OutputStream *olog = new NFTM::OutputStream("stderr");

	NFTM::SymbolTable *symtab = new NFTM::SymbolTable();
    symtab->ErrorLog(new NFTM::OutputStream("stderr"));

    NFTM::LoadAllFunctions(symtab);

	for (int idx = 1; idx < argc; idx++) {
		char *opt = argv[idx];
		char *val = opt;
		while (*val && *val != '=') {
			val++;
		}
		if (*val) {
			*(val++) = 0;
		} else {
			val = 0;
		}

		if (NFTM::StrCmp(opt, "--help")) {
			return 2;
		} else if (NFTM::StrCmp(opt, "--dump-env")) {
			symtab->Dump(olog, true, true);
		} else if (NFTM::StrCmp(opt, "--input") && val && *val) {
            if (inputFile) {
                oerr->Write("\nerror:\tyou may only specify one input file\n\n");
                return 2;
            }
            inputFile = new NFTM::Text(val);
            olog->Write(" info:\t%-20s == '%s'\n", "inputFile", val);
		} else if (NFTM::StrCmp(opt, "--output") && val && *val) {
            if (outputFile) {
                oerr->Write("\nerror:\tyou may only specify one output file\n\n");
                return 2;
            }
            outputFile = new NFTM::Text(val);
            olog->Write(" info:\t%-20s == '%s'\n", "outputFile", val);
		} else if (NFTM::StrCmp(opt, "--root-input") && val && *val) {
            olog->Write(" info:\t%-20s == '%s'\n", "rootInput", val);
            delete rootInput;
            rootInput = new NFTM::Text(val);
		} else if (NFTM::StrCmp(opt, "--root-output") && val && *val) {
            olog->Write(" info:\t%-20s == '%s'\n", "rootOutput", val);
            delete rootOutput;
            rootOutput = new NFTM::Text(val);
		} else if (NFTM::StrCmp(opt, "--variable") && val && *val) {
			char *name  = val;
			char *value = val;
			while (*value && *value != '=') {
				value++;
			}
			if (*value == '=') {
				*(value++) = 0;
			} else {
                value = 0;
            }
            NFTM::SymbolTableEntry *entry = symtab->Lookup(name);
            if (entry) {
                if (entry->isFinal) {
                    oerr->Write("\nerror:\tunable to update variable in symbol table\n");
                    oerr->Write("\tyou are not allowed to modify a finalized variable\n");
                    oerr->Write("\t%-20s == '%s'\n", "finalVar", name);
                    oerr->Write("\n");
                    return 2;
                }
                if (entry->kind == NFTM::steFunction && !symtab->Remove(entry->u.variable)) {
                    oerr->Write("\nerror:\tinternal error\n");
                    oerr->Write("\tunable to delete function from symbol table\n");
                    oerr->Write("\t%-20s == '%s'\n", "variableName", name);
                    oerr->Write("\n");
                    return 2;
                }
                if (entry->kind == NFTM::steVariable && !symtab->Remove(entry->u.variable)) {
                    oerr->Write("\nerror:\tinternal error\n");
                    oerr->Write("\tunable to delete variable from symbol table\n");
                    oerr->Write("\t%-20s == '%s'\n", "variableName", name);
                    oerr->Write("\n");
                    return 2;
                }
                delete entry;
            }
            if (!symtab->Add(name, new NFTM::Text(value))) {
                oerr->Write("\nerror:\tunable to add variable to symbol table\n");
                oerr->Write("\t%-20s == '%s'\n", "name", name);
                if (value) {
                    oerr->Write("\t%-20s == '%s'\n", "value", value);
                } else {
                    oerr->Write("\t%-20s == NULL\n", "value");
                }
                oerr->Write("\n");
                return 2;
            }
            olog->Write(" info:\t%-20s == '%s'\n", "name", name);
            olog->Write("\t%-20s == '%s'\n", "value", value);
		} else {
			oerr->Write("\nerror:\tinvalid option '%s%s%s'\n", opt, val ? "=" : "", val ? val : "");
			oerr->Write("\ttry --help if you're stuck\n\n");
			return 2;
		}
	}

    if (!inputFile) {
        oerr->Write("\nerror:\tyou must specify an input file to process\n\n");
        return 2;
    }

    // add site variables
    //
    symtab->Add(new NFTM::Variable("siteTitle" , new NFTM::Text("StaticCMS")));
    symtab->Add(new NFTM::Variable("siteSlogan", new NFTM::Text("moss grows fat on a static stone")));
    symtab->Add(new NFTM::Variable("cssDir"    , new NFTM::Text("css/")));
    
    // let us assume a default template directory
    //
    symtab->Add(new NFTM::Variable("templatePath", rootInput));
    
    // let us assume a default controller
    //
    symtab->Add(new NFTM::Variable("controller", new NFTM::Text("default")));

    NFTM::Text *fileName = new NFTM::Text(rootInput, inputFile);
    olog->Write(" info:\t%-20s == '%s'\n", "inputFileName", fileName->text);
    
    // read the file
    //
    NFTM::Text *input = new NFTM::Text(fileName, true, false);
    if (!input || !input->text) {
        perror(fileName->text);
        return 2;
    }

    // file format is
    //  ~~~
    //    variables
    //  ~~~
    //    text
    //
    // split the text file into the two sections
    //
    NFTM::Text *inputVariables = input->PullVariables();
    NFTM::Text *inputText      = input->PullText();
    symtab->Add(new NFTM::Variable("articleText", inputText));

    // add the variables from the input file to our symbol table
    //
    symtab->AddVariables(inputVariables);

    NFTM::SymbolTableEntry *inputControllerName = symtab->Lookup("controller");
    if (!inputControllerName) {
        oerr->Write("\nerror:\tunable to determine controller\n\n");
        return 2;
    } else if (inputControllerName->kind != NFTM::steVariable) {
        oerr->Write("\nerror:\tcontroller is wrong type - %d\n\n", inputControllerName->kind);
        return 2;
    }

    NFTM::Variable *varController = inputControllerName->u.variable;
    if (!varController->IsText()) {
        oerr->Write("\nerror:\tcontroller is not a text variable - %d\n", varController->kind);
        oerr->Write("\t%-20s == '%s'\n\n", "variableType", varController->Kind());
        return 2;
    }

    // this switch statement has to be changed for every install
    //
    NFTM::Controller *controller = 0;
    if (varController->u.text->Equals("article")) {
        controller = new NFTM::ArticleController(rootInput);
    }

    if (!controller) {
        oerr->Write("\nerror:\tunknown controller type '%s'\n\n", varController->u.text->text);
        return 2;
    }
    
    obuf = new NFTM::OutputStream(new NFTM::Text(rootOutput, outputFile));
    if (obuf->errmsg) {
        oerr->Write("\nerror:\tunable to create output file\n");
        oerr->Write("\t%-20s == '%s'\n", "fileName", obuf->fileName->text);
        oerr->Write("\t%-20s == '%s'\n", "errorMessage", obuf->errmsg->text);
        return 2;
    }
    oerr->Write("\t%-20s == '%s'\n", "fileName", obuf->fileName->text);

    // Handle processes the view and returns a Stack with
    // the output
    //
    NFTM::Stack *stack = new NFTM::Stack;
    if (!controller->Handle(symtab, stack)) {
        oerr->Write("\nerror:\tcontroller failed to load and execute request\n\n");
        symtab->Dump(olog, true, true);
        return 2;
    }

    if (stack->Render(obuf, oerr)) {
        olog->Write("\n info:\tsuccessfully rendered the stack\n\n");
    } else {
        oerr->Write("\nerror:\tunable to render the stack\n\n");
        return 2;
    }
    
    delete obuf;
    delete olog;
    delete oerr;
    
	return 0;
}
