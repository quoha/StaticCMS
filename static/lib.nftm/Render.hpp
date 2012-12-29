#ifndef   NFTM_static_src_bin_static_Render_HPP
#define   NFTM_static_src_bin_static_Render_HPP

namespace NFTM {
    
    //---------------------------------------------------------------------------
    // Render
    //    copies data in the stack to the output stream. responsible for
    //    escaping data if needed.
    //
    class Render {
    public:
        Render(void);
        ~Render() { }

        bool DoIt(class OutputStream *os, class Stack *stack);
    }; // class Render
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_Render_HPP
