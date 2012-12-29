#ifndef   NFTM_static_src_bin_static_View_HPP
#define   NFTM_static_src_bin_static_View_HPP

#include <vector>

namespace NFTM {

    //---------------------------------------------------------------------------
    // View
    //
    class View {
    public:
        View(const char *templateFile);
        View(const char *templatePath, const char *templateFile);
        ~View();

        // factory to spew out chunks. note that it updates the pointer to
        // the text to point to the character after the end of the chunk
        // that was returned. replace with your own chunk factory if you
        // need to change the chunk delimiters. i have no reasonable excuse
        // as to why this is a function rather than an class. none. at. all.
        //
        class Chunk *ChunkFactory(void);

        class Stack *Execute(class SymbolTable *symtab, class Stack *stack);

        char *path;
        char *file;
        char *name;

        // convenience variables for loading the template
        //
        bool  loadTemplate;
        char *text;

        std::vector<Chunk *> chunks;
    }; // class View

} // namespace NFTM

#endif // NFTM_static_src_bin_static_View_HPP
