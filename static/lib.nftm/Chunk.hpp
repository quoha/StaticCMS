#ifndef   NFTM_static_src_bin_static_Chunk_HPP
#define   NFTM_static_src_bin_static_Chunk_HPP

#include <vector>

namespace NFTM {

    //---------------------------------------------------------------------------
    // Chunk
    //    chunks are the blocks taken from the template. there are sub-classes
    //    for code and text chunks. each chunk knows how to deal with the stack.
    //    text chunks push a copy of themselves on to the stack. code chunks
    //    run the functions against the stack.
    //
    class Chunk {
    public:
        Chunk(char *text, int length);
        ~Chunk();

        virtual class Stack *Execute(class Stack *stack) = 0;

        char *text;
    }; // class Chunk

    //---------------------------------------------------------------------------
    // CodeChunk
    //    when executed, runs the text as functions against the stack
    //
    class CodeChunk : public Chunk {
    public:
        CodeChunk(char *text, int length);
        ~CodeChunk();

        class Stack *Execute(class Stack *stack);

        std::vector<char *> words;
    }; // class CodeChunk

    //---------------------------------------------------------------------------
    // TextChunk
    //     when executed, pushes a copy of text onto the stack
    //
    class TextChunk : public Chunk {
    public:
        TextChunk(char *text, int length);
        ~TextChunk();

        class Stack *Execute(class Stack *stack);
    }; // class TextChunk

} // namespace NFTM

#endif // NFTM_static_src_bin_static_Chunk_HPP
