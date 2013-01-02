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

    // must be very careful about stdout when using CGI
    //
    bool        useCGI     = true;

    NFTM::CGI  *cgi          = 0;
    NFTM::Text *inputFile    = 0;
    NFTM::Text *outputFile   = 0;
    NFTM::Text *pathInfo     = 0;
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
        } else if (NFTM::StrCmp(opt, "--cgi")) {
            if (!val || !*val) {
                useCGI = true;
            } else if (NFTM::StrCmp(val, "no") || NFTM::StrCmp(val, "false")) {
                useCGI = false;
            } else if (NFTM::StrCmp(val, "yes") || NFTM::StrCmp(val, "true")) {
                useCGI = true;
            } else {
                oerr->Write("\nerror:\tflag for %s must be yes, no, true or false\n\n", opt);
                return 2;
            }
            olog->Write(" info:\tturning CGI mode %s\n", useCGI ? "on" : "off");
		} else if (NFTM::StrCmp(opt, "--dump-env")) {
			symtab->Dump(olog, true, true);
		} else if (NFTM::StrCmp(opt, "--input") && val && *val) {
            if (useCGI) {
                oerr->Write("\nerror:\tyou may not specify an input file when using CGI\n\n");
                return 2;
            }
            if (inputFile) {
                oerr->Write("\nerror:\tyou may only specify one input file\n\n");
                return 2;
            }
            inputFile = new NFTM::Text(val);
            olog->Write(" info:\t%-20s == '%s'\n", "inputFile", val);
        } else if (NFTM::StrCmp(opt, "--no-cgi")) {
            useCGI = false;
            olog->Write(" info:\tturning CGI mode off\n");
		} else if (NFTM::StrCmp(opt, "--output") && val && *val) {
            if (outputFile) {
                oerr->Write("\nerror:\tyou may only specify one output file\n\n");
                return 2;
            }
            outputFile = new NFTM::Text(val);
            olog->Write(" info:\t%-20s == '%s'\n", "outputFile", val);
		} else if (NFTM::StrCmp(opt, "--path-info")) {
            delete pathInfo;
            pathInfo = new NFTM::Text(val);
		} else if (NFTM::StrCmp(opt, "--root-input") && val && *val) {
            olog->Write(" info:\t%-20s == '%s'\n", "rootInput", val);
            delete rootInput;
            rootInput = new NFTM::Text(val);
		} else if (NFTM::StrCmp(opt, "--root-output") && val && *val) {
            olog->Write(" info:\t%-20s == '%s'\n", "rootOutput", val);
            delete rootOutput;
            rootOutput = new NFTM::Text(val);
        } else if (NFTM::StrCmp(opt, "--variable") && useCGI) {
            oerr->Write("\nerror:\tyou can't override variables in CGI mode\n\n");
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

    if (useCGI) {
        // do something when running on the web
        //
        cgi = new NFTM::CGI();
        cgi->GetEnv("/", argv[0]);
        cgi->ExportToSymTab(symtab);
        pathInfo = cgi->PATH_INFO();
        olog->Write("\t%-20s == '%s'\n", "PATH_INFO", pathInfo->text);
        olog->Write("\n");
    } else {
        // do something when running from the command line
        //
        if (!outputFile) {
            outputFile = new NFTM::Text("stdout");
        }
    }

    obuf = new NFTM::OutputStream(outputFile);

    // start using the library code to do something useful
    //
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

    if (!c) {
        oerr->Write("\nerror:\tunable to find controller for route\n");
        oerr->Write("\t%-20s == '%s'\n", "PATH_INFO", pathInfo->text);
        oerr->Write("\n");
        return 2;
    }

    // Handle processes the view and returns a Stack with
    // the output
    //
    NFTM::Stack *stack = new NFTM::Stack;
    //stack->PushText("**** bottom of stack ***\n");
    if (!c->Handle(symtab, request, stack)) {
        oerr->Write("\nerror:\tcontroller failed to load and execute request\n\n");
        return 2;
    }
    //stack->PushText("**** top--- of stack ***\n");

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
