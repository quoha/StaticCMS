#include "local.hpp"

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
        if (b->variable == variable) {
            break;
        }

        b = b->next;
    }

    if (!b) {
        // didn't find the variable in the table
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
    b->variable = 0;
    
    delete b;
    
    return true;
}
