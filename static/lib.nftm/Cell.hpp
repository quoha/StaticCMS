#ifndef   NFTM_static_src_bin_static_Cell_HPP
#define   NFTM_static_src_bin_static_Cell_HPP

namespace NFTM {

class Cell {
public:
	Cell(class Number *n);
	Cell(class Stack *s);
	Cell(class Text *t);
	~Cell();

	class Number *AsNumber(void) { return n; }
	class Stack  *AsStack(void) { return s; }
	class Text   *AsText(void) { return t; }

	bool  IsNumber(void) const { return type == ccNumber; }
	bool  IsStack(void) const { return type == ccStack; }
	bool  IsText(void) const { return type == ccText; }

	
	enum { ccNumber, ccText, ccStack } type;

	class Number *n;
	class Stack  *s;
	class Text   *t;
}; // class Cell

} // namespace NFTM

#endif // NFTM_static_src_bin_static_Cell_HPP
