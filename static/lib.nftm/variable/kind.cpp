#include "local.hpp"

//============================================================================
// Kind(void)
//   returns type of object that word holds.
//
const char *NFTM::Variable::Kind(void) const {
	switch (kind) {
        case vtBOOL:
            return "boolean";
        case vtFUNCTION:
            return "function";
        case vtNULL:
            return "null";
        case vtNUMBER:
            return "number";
        case vtSTACK:
            return "stack";
        case vtTEXT:
            return "text";
        case vtOTHER:
            return "other";
	}
	return "unknown";
}
