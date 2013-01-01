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
#include "lib.nftm/Stack.hpp"
#include "lib.nftm/SymbolTable.hpp"
#include <stdio.h>

#define DNL fprintf(stderr, "%s: %d\n", __FILE__, __LINE__);

int main(int argc, char *argv[]) {
	stderr = stdout;

    bool        useCGI     = true;
    NFTM::Text *rootInput  = new NFTM::Text("./");
    NFTM::Text *rootOutput = new NFTM::Text("./");
	NFTM::OutputStream *os = new NFTM::OutputStream("stdout");

	FILE *fpOutput = stdout;

	NFTM::SymbolTable *symtab = new NFTM::SymbolTable();
    symtab->ErrorLog(new NFTM::OutputStream("stderr"));

	NFTM::CGI *cgi = new NFTM::CGI();
    cgi->GetEnv("/", argv[0]);
    cgi->ExportToSymTab(symtab);
    NFTM::Text *pathInfo = cgi->PATH_INFO();

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
        } else if (NFTM::StrCmp(opt, "--cgi")) {
            if (!val || !*val) {
                useCGI = true;
            } else if (NFTM::StrCmp(val, "no") || NFTM::StrCmp(val, "false")) {
                useCGI = false;
            } else if (NFTM::StrCmp(val, "yes") || NFTM::StrCmp(val, "true")) {
                useCGI = true;
            } else {
                fprintf(stderr, "\nerror:\tflag for %s must be yes, no, true or false\n\n", opt);
                return 2;
            }
		} else if (NFTM::StrCmp(opt, "--dump-env")) {
			symtab->Dump(os, true, true);
		} else if (NFTM::StrCmp(opt, "--output") && val && *val) {
			os->Redirect(val);
			if (os->ErrorMessage()) {
				fprintf(stderr, "%s: %s\n", val, os->ErrorMessage());
				return 2;
			}
        } else if (NFTM::StrCmp(opt, "--no-cgi")) {
            useCGI = false;
		} else if (NFTM::StrCmp(opt, "--path-info")) {
            delete pathInfo;
            pathInfo = new NFTM::Text(val);
		} else if (NFTM::StrCmp(opt, "--root-input") && val && *val) {
            printf(" info:\t%-20s == '%s'\n", "rootInput", val);
            delete rootInput;
            rootInput = new NFTM::Text(val);
		} else if (NFTM::StrCmp(opt, "--root-output") && val && *val) {
            printf(" info:\t%-20s == '%s'\n", "rootOutput", val);
            delete rootOutput;
            rootOutput = new NFTM::Text(val);
        } else if (NFTM::StrCmp(opt, "--variable") && useCGI) {
            fprintf(stderr, "\nerror:\tyou can't override variables in CGI mode\n\n");
            return 2;
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
                    printf("\nerror:\tunable to update variable in symbol table\n");
                    printf("\tyou are not allowed to modify a finalized variable\n");
                    printf("\t%-20s == '%s'\n", "finalVar", name);
                    printf("\n");
                    return 2;
                }
                if (entry->kind == NFTM::steFunction && !symtab->Remove(entry->u.variable)) {
                    printf("\nerror:\tinternal error\n");
                    printf("\tunable to delete function from symbol table\n");
                    printf("\t%-20s == '%s'\n", "variableName", name);
                    printf("\n");
                    return 2;
                }
                if (entry->kind == NFTM::steVariable && !symtab->Remove(entry->u.variable)) {
                    printf("\nerror:\tinternal error\n");
                    printf("\tunable to delete variable from symbol table\n");
                    printf("\t%-20s == '%s'\n", "variableName", name);
                    printf("\n");
                    return 2;
                }
                delete entry;
            }
            if (!symtab->Add(name, new NFTM::Text(value))) {
                printf("\nerror:\tunable to add variable to symbol table\n");
                printf("\t%-20s == '%s'\n", "name", name);
                if (value) {
                    printf("\t%-20s == '%s'\n", "value", value);
                } else {
                    printf("\t%-20s == NULL\n", "value");
                }
                printf("\n");
                return 2;
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

	NFTM::Request    *request  = new NFTM::Request(pathInfo);
	NFTM::Controller *c        = router.Route(request);
    printf("\t%-20s == '%s'\n", "PATH_INFO", pathInfo->text);
    printf("\n");

    if (!c) {
        printf("\nerror:\tunable to find controller for route\n");
        printf("\t%-20s == '%s'\n", "PATH_INFO", pathInfo->text);
        printf("\n");
        return 2;
    }

    // Handle processes the view and returns a Stack with
    // the output
    //
    NFTM::Stack *stack = new NFTM::Stack;
    //stack->PushText("**** bottom of stack ***\n");
    if (!c->Handle(symtab, request, stack)) {
        printf("\nerror:\tcontroller failed to load and execute request\n\n");
        return 2;
    }
    //stack->PushText("**** top--- of stack ***\n");

    if (!stack->Render(os, os)) {
        printf("\nerror:\tunable to render the stack\n\n");
        return 2;
    }

	if (os) {
		delete os;
	}

	if (fpOutput) {
		fclose(fpOutput);
	}

	return 0;
}
