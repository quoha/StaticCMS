#include "local.hpp"
#include "../Util.hpp"

//============================================================================
// Request(url)
//
NFTM::Request::Request(NFTM::Text *url) {
	argv    = 0;
	symtab  = new NFTM::SymbolTable();
	request = StrDup(url ? url->AsCString() : "/");

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
