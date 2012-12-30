#include "local.hpp"
#include "../Util.hpp"
#include "../Variable.hpp"

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
			symtab->Add(new NFTM::VarText(name, val));
		}
	}
}
