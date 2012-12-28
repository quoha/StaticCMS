#ifndef   NFTM_static_src_bin_static_Model_HPP
#define   NFTM_static_src_bin_static_Model_HPP

namespace NFTM {

    //---------------------------------------------------------------------------
    // Model
    //   this is the place for data. the model retrieves data from a source
    //   (a database or file or network pipe) and places it into the symbol
    //   table. the symbol table is then sent to the view.
    //
    //   tricky preemptive question - how do we handle sorting, things like
    //   "the five most recent posts"? i think that the answer is that the
    //   model adds data, data sets, and functions to the symbol table.
    //   the data set would be the list all posts and the function would
    //   return just the five most recent. i need to keep pondering this.
    //
    class Model {
    public:
        Model(class SymbolTable *symtab);
        ~Model();
        
        virtual bool Push(class Stack *stack, const char *word);
        
        class SymbolTable *symtab;
    }; // class Model
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_Model_HPP
