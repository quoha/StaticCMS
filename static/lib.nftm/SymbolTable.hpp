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
        
        // add various items to the table
        //
        class Variable *Add(class Function *function);
        class Variable *Add(class Number   *number);
        class Variable *Add(class Stack    *stack);
        class Variable *Add(class Text     *text);
        class Variable *Add(class Variable *variable);
        class Variable *Add(const char *name, const char *value);
        
        // find items in the table
        //
        class Variable *Lookup(const char *name) const;
        
        // miscellaneous
        //
        void            Dump(class OutputStream *os) const;
        
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
