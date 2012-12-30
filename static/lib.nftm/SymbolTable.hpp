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
        
        // find items in the table
        //
        class Variable *Lookup(const char *name) const;
        
        // miscellaneous
        //
        class OutputStream *ErrorLog(void) const { return errorLog; }
        void                ErrorLog(class OutputStream *errorLog_) { errorLog = errorLog_; }
        
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
        
        class OutputStream *errorLog;
    }; // class SymbolTable
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_SymbolTable_HPP
