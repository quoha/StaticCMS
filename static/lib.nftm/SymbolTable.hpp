#ifndef   NFTM_static_src_bin_static_SymbolTable_HPP
#define   NFTM_static_src_bin_static_SymbolTable_HPP

namespace NFTM {

//---------------------------------------------------------------------------
// SymbolTable
//    the interpreter uses the symbol table to store functions and variables.
//    it uses a chained hash table, so items with the same name will be
//    stored in the same chain. the chain is LIFO, so for any given name,
//    only the last item will be found on a lookup.
//
class SymbolTable {
	static const int hashSize = 1024;

public:
	SymbolTable(void);
	~SymbolTable();

    // add various items to the table
    //
	class Word     *Add(class Function *function);
	class Word     *Add(class Variable *var);
	class Word     *Add(class Word     *word);
	class Word     *Add(const char *name, const char *value);
    bool            Replace(class Word *word);
	bool            Update(const char *name, const char *value);

    // find items in the table
    //
	class Word     *Lookup(const char *name) const;

    // miscellaneous
    //
	void            Dump(class OutputStream *os) const;
	unsigned int    Hash(const char *str) const;

	struct Bucket {
        struct Bucket  *prev;
		struct Bucket  *next;
		unsigned int    hashValue;
		class Word     *word;
	} *hash[hashSize];

}; // class SymbolTable

} // namespace NFTM

#endif // NFTM_static_src_bin_static_SymbolTable_HPP
