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
    if (!data) {
        // open the file
        data = NFTM::StrCat(sSiteName, sPageTitle, sIncludeFile);

        if (data) {
            NFTM::Chunk *chunk = ChunkFactory();
            while (chunk) {
                chunks.push_back(chunk);
                chunk = ChunkFactory();
            }
        }
    }

    if (data && stack) {
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
