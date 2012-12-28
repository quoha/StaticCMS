#ifndef   NFTM_static_src_bin_static_Stack_HPP
#define   NFTM_static_src_bin_static_Stack_HPP

namespace NFTM {

//----------------------------------------------------------------------------
// Stack
//   manage a stack of pointers to Word objects
//
class Stack {
public:
	Stack(void);
	~Stack();

	// the classic stack interface
	//  * Push adds     an item to   the top of the stack
	//  * Pop  removes the item from the top of the stack
	//
	class Word *Pop(void) {
		return Top();
	}
	class Word *Push(class Word *word) {
		return Top(word);
	}

	// don't tell anyone, but we are really a double-ended queue
	//
	//  * bottom is the first item added
	//  * top    is the last  item added
	//
	class Word *Bottom(void);               // pop  word from bottom
	class Word *Bottom(class Word *word);   // push word to   bottom
	class Word *Top(void);                  // pop  word from top
	class Word *Top(class Word *word);      // push word to   top

	struct StackNode {
		struct StackNode *prev;  // towards bottom of stack
		class  Word      *word;
		struct StackNode *next;  // towards top    of stack
	} *bottom, *top;
}; // class Stack

} // namespace NFTM

#endif // NFTM_static_src_bin_static_Stack_HPP
