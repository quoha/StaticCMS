#ifndef   NFTM_static_src_bin_static_Chunk_HPP
#define   NFTM_static_src_bin_static_Chunk_HPP

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
        Chunk(char *text);
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
        CodeChunk(char *text);
        ~CodeChunk();

        class Stack *Execute(class Stack *stack);
    }; // class CodeChunk

    //---------------------------------------------------------------------------
    // TextChunk
    //     when executed, pushes a copy of text onto the stack
    //
    class TextChunk : public Chunk {
    public:
        TextChunk(char *text);
        ~TextChunk();

        class Stack *Execute(class Stack *stack);
    }; // class TextChunk

    // factory to spew out chunks. note that it updates the pointer to
    // the text to point to the character after the end of the chunk
    // that was returned. replace with your own chunk factory if you
    // need to change the chunk delimiters. i have no reasonable excuse
    // as to why this is a function rather than an class. none. at. all.
    //
    Chunk *ChunkFactory(char * & text);

} // namespace NFTM

#endif // NFTM_static_src_bin_static_Chunk_HPP
