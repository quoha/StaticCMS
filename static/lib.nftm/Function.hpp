#ifndef   NFTM_static_src_bin_static_Function_HPP
#define   NFTM_static_src_bin_static_Function_HPP

namespace NFTM {

//----------------------------------------------------------------------------
// Function
//   the Function class manipulates the stack.
//
//   it's an abstract base class, so inherit and extend, please.
//
//   btw, please be sure to set the name.
//
class Function {
public:
	virtual ~Function() = 0;
	Function(void) {
		name = "";
	}

	const char *Name(void) const {
		return name;
	}

	virtual bool Execute(class Stack *stack) = 0;

	const char *name;

}; // class Function

} // namespace NFTM

#endif // NFTM_static_src_bin_static_Function_HPP
