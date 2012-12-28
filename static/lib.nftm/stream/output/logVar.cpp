#include "../local.hpp"
#include "../../Variable.hpp"

//============================================================================
// LogVar(var)
//
bool NFTM::OutputStream::LogVar(NFTM::Variable *var) {
	if (data) {
		fprintf((FILE *)data, "%-25s == '%s'\n", var->Name(), "var->Name()");
	}

	return data ? true : false;
}
