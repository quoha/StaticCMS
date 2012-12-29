#include "local.hpp"
#include "../Util.hpp"

static const char *sSiteName = "<p>Site_Name is <billy site_name /></p>";
static const char *sPageTitle = "<p>Page_Title is <billy page_title /></p>";
static const char *sIncludeFile = "<billy 'filename.tpl' include />";

//============================================================================
// Execute(stack)
//    loads the template if needed, then executes the chunks in the template.
//
NFTM::Stack *NFTM::View::Execute(NFTM::Stack *stack) {
    if (loadTemplate) {
        // open the file
        //
        // not really. dummy this up for development
        //
        char *data = NFTM::StrCat(sSiteName, sPageTitle, sIncludeFile);
        
        text = data;
        
        // convert the template into chunks
        //
        for (NFTM::Chunk *chunk = ChunkFactory(); chunk; chunk = ChunkFactory()) {
            chunks.push_back(chunk);
        }
        
        // delete data since the chunks made a private copy
        //
        delete [] data;
        data = 0;

        // disable the variables so that we don't load the template again
        //
        loadTemplate = false;
        text         = 0;
    }

    if (stack) {
        // iterate through all of the chunks in the view
        //
        std::vector<Chunk *>::iterator i;
        for (i = chunks.begin(); i != chunks.end(); ++i) {
            // execute the chunk
            //
            if (!(*i)->Execute(stack)) {
                return 0;
            }
        }
    }
    
    return stack;
}
