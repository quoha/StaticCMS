#include "local.hpp"

//============================================================================
// Top(variable)
//   pushes variable on top of the stack
//
NFTM::Variable *NFTM::Stack::Top(NFTM::Variable *variable) {
	// StackNode is a wrapper for every variable that we push
	//
	struct StackNode *last = new StackNode();

	// link the new node to the top of the list
	//
	last->prev     = top;
	last->variable = variable;
	last->next     = 0;

	// we're really a double ended queue, so fix up the top and bottom
	// pointers as needed.
	//
	if (!bottom) {
		bottom = top = last;
	} else {
		top->next = last;
		top = last;
	}

	return variable;
}

//============================================================================
// Top()
//   removes variable on top of the stack
//   returns that variable or null if the stack is empty
//
NFTM::Variable *NFTM::Stack::Top(void) {
	struct StackNode *last     = top;
	NFTM::Variable   *variable = last ? last->variable : 0;

	// unlink the last node from the list
	//
	if (last) {
		top = top->prev;

		// we're really a double ended queue, so fix
		// up the top and bottom pointers as needed
		//
		if (top) {
			top->next = 0;
		} else {
			bottom = top = 0;
		}

		// i don't know why this fixed a memory leak
		//
		last->prev = 0;
		last->next = 0;

		// and free up the memory
		//
		delete last;
	}

	return variable;
}
