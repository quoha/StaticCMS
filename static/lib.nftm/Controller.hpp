#ifndef   NFTM_static_src_bin_static_Controller_HPP
#define   NFTM_static_src_bin_static_Controller_HPP

namespace NFTM {

class Controller {
public:
	Controller(void);
	virtual ~Controller();

	virtual bool CanHandle(class Request *request) = 0;
	virtual bool Handle(class SymbolTable *symtab, class Request *request, class Stack *stack) = 0;
}; // class Controller

} // namespace NFTM

#endif // NFTM_static_src_bin_static_Controller_HPP
