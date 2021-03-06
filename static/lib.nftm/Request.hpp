#ifndef   NFTM_static_src_bin_static_Request_HPP
#define   NFTM_static_src_bin_static_Request_HPP

namespace NFTM {
    
    class Request {
    public:
        Request(class Text *url);
        ~Request();
        
        void Dump(class OutputStream *os);
        void ExtractQueryStrings(void);
        void RequestToPath(void);
        
        char              *request;
        char              *queryString;
        class SymbolTable *symtab;
        char             **argv;
    }; // class Request
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_Request_HPP
