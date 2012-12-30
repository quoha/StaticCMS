#include "local.hpp"

//============================================================================
// Bottom(variable)
//   pushes variable on bottom of the stack
//
NFTM::Variable *NFTM::Stack::Bottom(NFTM::Variable *variable) {
	// StackNode is a wrapper for every word that we push
	//
	struct StackNode *first = new StackNode();

	// link the new node to the bottom of the list
	//
	first->prev     = 0;
	first->variable = variable;
	first->next     = bottom;

	// we're really a double ended queue, so fix up the top and bottom
	// pointers as needed.
	//
	if (!bottom) {
		bottom = top = first;
	} else {
		bottom->prev = first;
		bottom = first;
	}

	return variable;
}

//============================================================================
// Bottom()
//   removes variable on bottom of the stack
//   returns that variable or null if the stack is empty
//
NFTM::Variable *NFTM::Stack::Bottom(void) {
	struct StackNode *first = bottom;
	NFTM::Variable   *variable = first ? first->variable : 0;

	// unlink the first node from the list
	//
	if (first) {
		bottom = bottom->next;

		// we're really a double ended queue, so fix
		// up the top and bottom pointers as needed
		//
		if (bottom) {
			bottom->prev = 0;
		} else {
			bottom = top = 0;
		}

		// i don't know why this fixed a memory leak
		//
		first->prev = 0;
		first->next = 0;

		// and free up the memory
		//
		delete first;
	}

	return variable;
}
