#ifndef   NFTM_static_src_bin_static_Model_HPP
#define   NFTM_static_src_bin_static_Model_HPP

namespace NFTM {

class Model {
public:
	Model(void);
	~Model();

	virtual bool Push(class Stack *stack, const char *word);

}; // class Model

} // namespace NFTM

#endif // NFTM_static_src_bin_static_Model_HPP
