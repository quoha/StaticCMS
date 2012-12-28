#include "local.hpp"

//============================================================================
// Top(word)
//   pushes word on top of the stack
//
NFTM::Word *NFTM::Stack::Top(NFTM::Word *word) {
	// StackNode is a wrapper for every word that we push
	//
	struct StackNode *last = new StackNode();

	// link the new node to the top of the list
	//
	last->prev = top;
	last->word = word;
	last->next = 0;

	// we're really a double ended queue, so fix up the top and bottom
	// pointers as needed.
	//
	if (!bottom) {
		bottom = top = last;
	} else {
		top->next = last;
		top = last;
	}

	return word;
}

//============================================================================
// Top()
//   removes word on top of the stack
//   returns that word or null if the stack is empty
//
NFTM::Word *NFTM::Stack::Top(void) {
	struct StackNode *last = top;
	NFTM::Word       *word = last ? last->word : 0;

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

	return word;
}
