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
    public:
        SymbolTable(void);
        ~SymbolTable();
        
        // add various items to the table. note the convenience function
        // for c-strings. i hope that by this point, we're ready to stop
        // using them. and maybe sometime soon i'll step up to real strings.
        //
        class Variable *Add(class Variable *variable);
        class Variable *Add(const char *name, class Number   *number);
        class Variable *Add(const char *name, class Stack    *stack);
        class Variable *Add(const char *name, class Text     *text);
        class Variable *Add(const char *name, class Text     *text, int length);
        class Variable *Add(const char *name, const char     *text);
        class Variable *Add(const char *name, const char     *text, int length);
        
        // find items in the table
        //
        class Variable *Lookup(const char *name) const;
        
        // miscellaneous
        //
        void Dump(class OutputStream *os, bool showHash, bool showVar) const;
        bool Remove(class Variable *variable);
        
    private:
        static const int hashSize = 1024;
        
        unsigned int Hash(const char *str) const;
        
        struct Bucket {
            struct Bucket  *prev;
            struct Bucket  *next;
            unsigned int    hashValue;
            class Variable *variable;
        } *hash[hashSize];
        
    }; // class SymbolTable
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_SymbolTable_HPP
