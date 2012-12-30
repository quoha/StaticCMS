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

// TODO
//  * subclass Variables instead of using union

#include "local.hpp"
#include <stdio.h>

#define DNL fprintf(stderr, "%s: %d\n", __FILE__, __LINE__);

int main(int argc, char *argv[]) {
	stderr = stdout;

    NFTM::Render render;
	NFTM::OutputStream *os = new NFTM::OutputStream("stdout");

	FILE *fpOutput = stdout;

	NFTM::SymbolTable *symtab = new NFTM::SymbolTable();

	NFTM::CGI *cgi = new NFTM::CGI();
    cgi->GetEnv("/", argv[0]);
    cgi->ExportToSymTab(symtab);

    LoadAllFunctions(symtab);

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
			symtab->Dump(os, true, true);
		} else if (NFTM::StrCmp(opt, "--output") && val && *val) {
			os->Redirect(val);
			if (os->ErrorMessage()) {
				fprintf(stderr, "%s: %s\n", val, os->ErrorMessage());
				return 2;
			}
		} else if (NFTM::StrCmp(opt, "--template") && val && *val) {
			NFTM::Text *t = new NFTM::Text();
			if (!t->FromFile(val, true)) {
				perror(val);
				return 2;
			}
			fprintf(fpOutput, "%s\n\n", t->data ? t->data : "");
			delete t;
		} else if (NFTM::StrCmp(opt, "--variable") && val && *val) {
			char *name  = val;
			char *value = val;
			while (*value && *value != '=') {
				value++;
			}
			if (*value == '=') {
				*(value++) = 0;
			}
            NFTM::Variable *variable = symtab->Lookup(name);
            if (variable) {
                if (!variable->Value(value)) {
                    printf("\nerror:\tunable to update variable in symbol table\n");
                    printf("\t%-20s == '%s'\n", "name", name);
                    printf("\t%-20s == '%s'\n\n", "value", value);
                    return 2;
                }
            } else {
                if (!symtab->Add(name, value)) {
                    printf("\nerror:\tunable to add variable to symbol table\n");
                    printf("\t%-20s == '%s'\n", "name", name);
                    printf("\t%-20s == '%s'\n\n", "value", value);
                    return 2;
                }
            }
            printf(" info:\t%-20s == '%s'\n", "name", name);
            printf("\t%-20s == '%s'\n", "value", value);
		} else {
			fprintf(stderr, "\nerror:\tinvalid option '%s%s%s'\n", opt, val ? "=" : "", val ? val : "");
			fprintf(stderr, "\ttry --help if you're stuck\n\n");
			return 2;
		}
	}

	NFTM::Router         router;
	NFTM::PostController post;

	// default is used if no other controllers accept the route
	//
	router.DefaultController(new NFTM::DefaultController);

	// add the controllers in FIFO order
	//
	router.AddController(&post);

    NFTM::Variable   *pathInfo = cgi->PATH_INFO();
	NFTM::Request    *request = new NFTM::Request(pathInfo ? pathInfo->AsText() : 0);
	NFTM::Controller *c       = router.Route(request);

    if (!c) {
        printf("\nerror:\tunable to find controller for route\n");
        printf("\t%-20s == '%s'\n", "PATH_INFO", pathInfo ? pathInfo->AsText()->AsCString() : "");
        printf("\n");
        return 2;
    }

    // Handle processes the view and returns a Stack with
    // the output
    //
    NFTM::Stack *stack = new NFTM::Stack;
    stack->PushText("**** bottom of stack ***\n");
    if (!c->Handle(symtab, request, stack)) {
        printf("\nerror:\tcontroller did not create a stack\n\n");
        return 2;
    }
    stack->PushText("**** bottom of stack ***\n");

    if (!stack->Render(os)) {
        printf("\nerror:\tunable to render the stack\n\n");
        return 2;
    }
    render.DoIt(os, stack);

	if (os) {
		delete os;
	}

	if (fpOutput) {
		fclose(fpOutput);
	}

	return 0;
}
