#include "SymbolTable.hpp"
#include "Function.hpp"
#include "Stream.hpp"
#include "Text.hpp"
#include "Util.hpp"
#include "Variable.hpp"
#include <ctype.h>
#include <cstring>

//============================================================================
// SymbolTable(void)
//
NFTM::SymbolTable::SymbolTable(void) {
    debugLog = 0;
    errorLog = 0;
	for (int idx = 0; idx < hashSize; idx++) {
		hash[idx] = 0;
	}
}

//============================================================================
// ~SymbolTable()
//
NFTM::SymbolTable::~SymbolTable() {
	for (int idx = 0; idx < hashSize; idx++) {
		Bucket *b = hash[idx];
		while (b) {
			Bucket *tmp = b->next;
			delete b;
			b = tmp;
		}
	}
    delete debugLog;
    delete errorLog;
}

//============================================================================
// Add(function)
//
NFTM::SymbolTableEntry *NFTM::SymbolTable::Add(NFTM::Function *function, bool isFinal) {
	Bucket *b = new Bucket();
    
    b->entry             = new SymbolTableEntry;
    b->entry->name       = StrDup(function->Name());
    b->entry->kind       = steFunction;
    b->entry->u.function = function;
    b->entry->isFinal    = isFinal;

	b->hashValue         = Hash(b->entry->name);
    b->prev              = 0;
	b->next              = hash[b->hashValue % hashSize];
    if (b->next) {
        b->next->prev = b;
    }
    
	hash[b->hashValue % hashSize] = b;
    
	return b->entry;
}

//============================================================================
// Add(name, text)
//
NFTM::SymbolTableEntry *NFTM::SymbolTable::Add(const char *name, NFTM::Text *text) {
	Bucket *b = new Bucket();
    
    b->entry             = new SymbolTableEntry;
    b->entry->name       = StrDup(name);
    b->entry->kind       = steText;
    b->entry->u.text     = text;
    b->entry->isFinal    = false;
    
	b->hashValue         = Hash(b->entry->name);
    b->prev              = 0;
	b->next              = hash[b->hashValue % hashSize];
    if (b->next) {
        b->next->prev = b;
    }
    
	hash[b->hashValue % hashSize] = b;
    
	return b->entry;
}

//============================================================================
// Add(variable)
//
NFTM::SymbolTableEntry *NFTM::SymbolTable::Add(NFTM::Variable *variable) {
	Bucket *b = new Bucket();
    
    b->entry             = new SymbolTableEntry;
    b->entry->name       = StrDup(variable->Name());
    b->entry->kind       = steVariable;
    b->entry->u.variable = variable;
    b->entry->isFinal    = false;
    
	b->hashValue         = Hash(b->entry->name);
    b->prev              = 0;
	b->next              = hash[b->hashValue % hashSize];
    if (b->next) {
        b->next->prev = b;
    }
    
	hash[b->hashValue % hashSize] = b;
    
	return b->entry;
}

//============================================================================
// AddVariables(text)
//
// NOTE - overwrites data in the input text
//
void NFTM::SymbolTable::AddVariables(NFTM::Text *text) {
    char *s = text->text;

    while (*s) {
        // skip leading spaces on the current line
        //
        while (*s && isspace(*s)) {
            *(s++) = 0;
        }

        char *name = s;

        // advance to end of name
        //
        while (*s && !isspace(*s)) {
            s++;
        }

        // advance to start of value
        //
        while (*s && *s != '\n' && isspace(*s)) {
            *(s++) = 0;
        }

        char *value = s;
        
        // advance to end of value
        //
        while (*s && *s != '\n') {
            s++;
        }

        if (*s) {
            *(s++) = 0;
        }
        
        if (*name) {
            Add(new NFTM::Variable(name, new NFTM::Text(value)));
        }
    }
}

//============================================================================
// Dump()
//
void NFTM::SymbolTable::Dump(NFTM::OutputStream *os, bool showHash, bool showVar) const {
	os->Write(" dump:\tSymbolTable ----------------------------------------------\n");

	for (int idx = 0; idx < hashSize; idx++) {
		Bucket *b = hash[idx];
		for (int idy = 0; b; idy++, b = b->next) {
			if (idy == 0) {
				os->Write("%5d:\t-----------\n", idx);
			}
            if (!showHash && !showVar) {
                os->Write("\tvar %s\n", b->entry->name);
            }
            if (showHash) {
                if (showVar) {
                    os->Write("\thash value %16x %8d\n", b->hashValue, b->entry->kind);
                } else {
                    os->Write("\thash value %16x %s\n", b->hashValue, b->entry->name);
                }
            }
            if (showVar && b->entry->kind == steVariable) {
                b->entry->u.variable->Dump(os);
            }
		}
	}
    
	os->Write(" dump:\t----------------------------------------------------------\n");
}

//============================================================================
// Hash(text)
//
unsigned int NFTM::SymbolTable::Hash(const char *str) const {
	unsigned int djbHash = 0;
    
	while (*str) {
		djbHash  = (djbHash *       33) + (*str);
        
		str++;
	}
    
	return djbHash;
}

//============================================================================
// Lookup(const char *name)
//    searchs the table for an item with the name. note that if there
//    are multiple items with the same name, only the first one found
//    will be returned.
//
// RETURN
//    NULL      no item found
//    not-NULL  the address of the first item with the same name
//
NFTM::SymbolTableEntry *NFTM::SymbolTable::Lookup(const char *name) const {
	unsigned int hashValue = Hash(name);
    
	Bucket *b = hash[hashValue % hashSize];
    
	while (b) {
		if (b->hashValue == hashValue) {
			if (std::strcmp(name, b->entry->name) == 0) {
				return b->entry;
			}
		}
        
		b = b->next;
	}
    
	return 0;
}

//============================================================================
// Remove(function)
//   removes a function from the symbol table. does not delete the function.
//
// RETURN
//   true   the function existed in the table and was removed
//   false  the function was not in the table
//
bool NFTM::SymbolTable::Remove(NFTM::Function *function) {
    unsigned int hashValue = Hash(function->Name());
    
	Bucket *b = hash[hashValue % hashSize];
    
    while (b) {
        if (b->entry->kind == steFunction && b->entry->u.function == function) {
            break;
        }
        
        b = b->next;
    }
    
    if (!b) {
        // didn't find the function in the table
        //
        return false;
    }
    
    // found the function in the table

    // if it is at the start of the chain, reset the pointer
    // so that we don't lose the chain.
    //
    if (b == hash[hashValue % hashSize]) {
        hash[hashValue % hashSize] = b->next;
    }
    
    // unlink the bucket from the existing chain
    //
    if (b->prev) {
        b->prev->next = b->next;
    }
    if (b->next) {
        b->next->prev = b->prev;
    }
    
    // unlink the bucket's reference so that nothing
    // extra gets freed when the bucket is deleted
    //
    b->prev     = 0;
    b->next     = 0;
    b->entry    = 0;
    
    delete b;
    
    return true;
}

//============================================================================
// Remove(variable)
//   removes a variable from the symbol table. does not delete the variable.
//
// RETURN
//   true   the variable existed in the table and was removed
//   false  the variable was not in the table
//
bool NFTM::SymbolTable::Remove(NFTM::Variable *variable) {
    unsigned int hashValue = Hash(variable->Name());
    
	Bucket *b = hash[hashValue % hashSize];
    
    while (b) {
        if (b->entry->kind == steVariable && b->entry->u.variable == variable) {
            break;
        }
        
        b = b->next;
    }
    
    if (!b) {
        // didn't find the variable in the table
        //
        return false;
    }
    
    // found the variable in the table
    
    // if it is at the start of the chain, reset the pointer
    // so that we don't lose the chain.
    //
    if (b == hash[hashValue % hashSize]) {
        hash[hashValue % hashSize] = b->next;
    }
    
    // unlink the bucket from the existing chain
    //
    if (b->prev) {
        b->prev->next = b->next;
    }
    if (b->next) {
        b->next->prev = b->prev;
    }
    
    // unlink the bucket's reference so that nothing
    // extra gets freed when the bucket is deleted
    //
    b->prev     = 0;
    b->next     = 0;
    b->entry    = 0;
    
    delete b;
    
    return true;
}
