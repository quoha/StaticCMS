#ifndef   NFTM_static_src_bin_static_CGI_HPP
#define   NFTM_static_src_bin_static_CGI_HPP

namespace NFTM {
    
    class CGI {
    public:
        CGI(void);
        ~CGI();
        
        void            DumpEnv(class OutputStream *os) const;
        bool            ExportToSymTab(class SymbolTable *symtab);
        bool            GetEnv(const char *defaultPath, const char *defaultScriptName);
        
        class Variable *AUTH_TYPE        (void) const;
        class Variable *CONTENT_LENGTH   (void) const;
        class Variable *CONTENT_TYPE     (void) const;
        class Variable *GATEWAY_INTERFACE(void) const;
        class Variable *PATH             (void) const;
        class Variable *PATH_INFO        (void) const;
        class Variable *PATH_TRANSLATED  (void) const;
        class Variable *QUERY_STRING     (void) const;
        class Variable *REMOTE_ADDR      (void) const;
        class Variable *REMOTE_HOST      (void) const;
        class Variable *REMOTE_IDENT     (void) const;
        class Variable *REMOTE_USER      (void) const;
        class Variable *REQUEST_METHOD   (void) const;
        class Variable *SCRIPT_NAME      (void) const;
        class Variable *SERVER_NAME      (void) const;
        class Variable *SERVER_PORT      (void) const;
        class Variable *SERVER_PROTOCOL  (void) const;
        class Variable *SERVER_SOFTWARE  (void) const;
        
        class Variable *authType;
        class Variable *contentLength;
        class Variable *contentType;
        class Variable *gatewayInterface;
        class Variable *path;
        class Variable *pathInfo;
        class Variable *pathTranslated;
        class Variable *queryString;
        class Variable *remoteAddr;
        class Variable *remoteHost;
        class Variable *remoteIdent;
        class Variable *remoteUser;
        class Variable *requestMethod;
        class Variable *scriptName;
        class Variable *serverName;
        class Variable *serverPort;
        class Variable *serverProtocol;
        class Variable *serverSoftware;
    }; // class CGI
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_CGI_HPP
