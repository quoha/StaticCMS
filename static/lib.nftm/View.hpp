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
        ~View();

        class Stack *DoIt(class Stack *stack);

        char *path;
        char *name;

        std::vector<Chunk> chunks;
    }; // class View

} // namespace NFTM

#endif // NFTM_static_src_bin_static_View_HPP
