#include "Request.hpp"
#include "Stream.hpp"
#include "SymbolTable.hpp"
#include "Text.hpp"
#include "Util.hpp"
#include "Variable.hpp"
#include <stdio.h>

//============================================================================
// Request(url)
//
NFTM::Request::Request(NFTM::Text *url) {
	argv    = 0;
	symtab  = new NFTM::SymbolTable();
	request = StrDup(!url || url->IsNull() ? "/" : url->text);
    
	// split the url at the question mark
	//
	queryString = request;
	while (*queryString && *queryString != '?') {
		queryString++;
	}
	if (*queryString) {
		*(queryString++) = 0;
	}
    
	// make the request canonical
	//
	AbsPath(request);
    
	// convert the request into path elements
	//
	RequestToPath();
    
	// push the query string variables into the symbol table
	// format is name=value; or name=value&
	// value is optional, name isn't
	//
	ExtractQueryStrings();
}


//---------------------------------------------------------------------------
//
void NFTM::Request::Dump(NFTM::OutputStream *os) {
    if (os) {
        os->Write("\t\trequest %s\n", request);
        os->Write("\t\t  query %s\n", queryString);
        os->Write("\t\t symtab %s\n", symtab ? "present" : "missing");
        for (int idx = 0; argv[idx]; idx++) {
            os->Write("\t\t    %3d '%s'\n", idx, argv[idx]);
        }
    }
}

//============================================================================
// ExtractQueryStrings()
//
void NFTM::Request::ExtractQueryStrings(void) {
	// push the query string variables into the symbol table
	// format is name=value; or name=value&
	// value is optional, name isn't
	//
	char *s = queryString;
	while (*s) {
		while (*s && (*s == ';' || *s == '&')) {
			s++;
		}
		if (*s == ';' || *s == '&') {
			*(s++) = 0;
		}
        
		// point name to start of string
		//
		char *name = s;
		char *val  = s;
        
		// find end of string
		//
		while (*s && !(*s == ';' || *s == '&')) {
			s++;
		}
		if (*s) {
			*(s++) = 0;
		}
        
		// point val to the part after the =
		//
		while (*val && *val != '=') {
			val++;
		}
		if (*val) {
			*(val++) = 0;
		}

		if (*name) {
            NFTM::Text *queryName = new NFTM::Text("?", name);
			symtab->Add(queryName->text, new NFTM::Text(val));
		}
	}
}

//============================================================================
// RequestToPath()
//   convert the request into path elements
//   no matter what, argv[0] should always be /
//
void NFTM::Request::RequestToPath(void) {
    static char loneSlash[2] = {'/', 0};
    
	if (argv) {
		return;
	}
    
	// count the /
	//
	int   numberOfSlashes = 0;
	char *s = request;
	while (*s) {
		if (*(s++) == '/') {
			numberOfSlashes++;
		}
	}
    
	// create storage for them. the "+3" allows for a null
	// pointer to terminate the list as well as for the possibility
	// that the request does not start or end with a slash.
	//
	argv = new char *[numberOfSlashes + 3];
    
    int idx = 0;
    s = request;
    
    if (*s == '/') {
        argv[idx++] = loneSlash;
        s++;
    }
    
	// assign the remaining path elements to argv
	//
	while (*s) {
		while (*s == '/') {
			*(s++) = 0;
		}
        
		argv[idx++] = s;
        
		while (*s && *s != '/') {
			s++;
		}
	}
    
    // null terminate the list to make life simpler
    //
	argv[idx] = 0;
}
