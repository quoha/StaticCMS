#include "../local.hpp"
#include <cstring>

//============================================================================
// Push(stack, word)
//
bool NFTM::PostModel::Push(NFTM::Stack *stack, const char *word) {
	if (std::strcmp(word, "hello") == 0) {
		//stack->PushText(new NFTM::Text("hello"));
	} else {
		// don't know the word
		return false;
	}

	return true;
}
