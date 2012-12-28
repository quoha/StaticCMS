#ifndef   NFTM_static_src_bin_static_Word_HPP
#define   NFTM_static_src_bin_static_Word_HPP

namespace NFTM {

//----------------------------------------------------------------------------
// Word
// the Word class is the basic unit of the stack. it can accept any type
// that the interpreter will deal with.
//
class Word {
public:
	Word(void);
	Word(class Function *function);
	Word(class Number *number);
	Word(class Stack *stack);
	Word(class Text *text);
	Word(class Variable *variable);
	~Word();

	class Function *AsFunction(void) { return kind == wtFUNCTION ? val.function : 0; }
	class Number   *AsNumber(void) { return kind == wtNUMBER ? val.number : 0; }
	class Stack    *AsStack(void) { return kind == wtSTACK ? val.stack : 0; }
	class Text     *AsText(void) { return kind == wtTEXT ? val.text : 0; }
	class Variable *AsVariable(void) { return kind == wtVARIABLE ? val.variable : 0; }

	bool IsFunction(void) const { return kind == wtFUNCTION; }
	bool IsNumber(void) const { return kind == wtNUMBER; }
	bool IsStack(void) const { return kind == wtSTACK; }
	bool IsTainted(void) const { return isTainted; }
	bool IsText(void) const { return kind == wtTEXT; }
	bool IsVariable(void) const { return kind == wtVARIABLE; }

	const char *Kind(void) const;
	const char *Name(void) const;

	bool isTainted;
	enum { wtFUNCTION, wtNUMBER, wtNOOP, wtSTACK, wtTEXT, wtVARIABLE } kind;
	union {
		class Function *function;
		class Number   *number;
		class Stack    *stack;
		class Text     *text;
		class Variable *variable;
	} val;
}; // class Word

} // namespace NFTM

#endif // NFTM_static_src_bin_static_Word_HPP
