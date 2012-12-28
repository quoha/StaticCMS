#ifndef   NFTM_static_src_bin_static_Controller_HPP
#define   NFTM_static_src_bin_static_Controller_HPP

namespace NFTM {

class Controller {
public:
	Controller(void);
	~Controller();

	virtual bool CanHandle(class Request *request);
	virtual bool Handle(class SymbolTable *symtab, class Request *request, class OutputStream *os);
}; // class Controller

} // namespace NFTM

#endif // NFTM_static_src_bin_static_Controller_HPP
