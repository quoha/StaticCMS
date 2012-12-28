#include "local.hpp"

//============================================================================
// Kind(void)
//   returns type of object that word holds.
//
const char *NFTM::Variable::Kind(void) const {
	switch (kind) {
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
	}
	return "unknown";
}
