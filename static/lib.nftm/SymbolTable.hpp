#ifndef   NFTM_static_src_bin_static_SymbolTable_HPP
#define   NFTM_static_src_bin_static_SymbolTable_HPP

namespace NFTM {

    //---------------------------------------------------------------------------
    //
    enum symtabEntryType {steBoolean, steFunction, steNull, steText, steVariable};

    //---------------------------------------------------------------------------
    // SymbolTableEntry
    //
    struct SymbolTableEntry {
        symtabEntryType     kind;
        char               *name;
        bool                isFinal;
        union {
            bool            boolean;
            class Function *function;
            void           *null;
            class Text     *text;
            class Variable *variable;
        } u;
    }; // struct SymbolTableEntry

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
        
        // add entries to the table
        //
        SymbolTableEntry *Add(class Function *function, bool isFinal);
        SymbolTableEntry *Add(const char     *name    , class Text *text);
        SymbolTableEntry *Add(class Variable *variable);
        
        // find items in the table
        //
        SymbolTableEntry *Lookup(const char *name) const;
        
        // miscellaneous
        //
        class OutputStream *ErrorLog(void) const { return errorLog; }
        void                ErrorLog(class OutputStream *errorLog_) { errorLog = errorLog_; }
        
        void Dump(class OutputStream *os, bool showHash, bool showVar) const;
        bool Remove(class Function *function);
        bool Remove(class Variable *variable);
        
    private:
        static const int hashSize = 1024;
        
        unsigned int Hash(const char *str) const;
        
        struct Bucket {
            struct Bucket    *prev;
            struct Bucket    *next;
            unsigned int      hashValue;
            SymbolTableEntry *entry;
        } *hash[hashSize];

        class OutputStream *debugLog;
        class OutputStream *errorLog;
    }; // class SymbolTable
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_SymbolTable_HPP
