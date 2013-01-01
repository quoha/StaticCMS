#ifndef   NFTM_static_src_bin_static_CGI_HPP
#define   NFTM_static_src_bin_static_CGI_HPP

namespace NFTM {
    
    class CGI {
    public:
        CGI(void);
        ~CGI();
        
        void        DumpEnv(class OutputStream *os) const;
        bool        ExportToSymTab(class SymbolTable *symtab);
        bool        GetEnv(const char *defaultPath, const char *defaultScriptName);
        
        class Text *AUTH_TYPE        (void) const { return authType;         }
        class Text *CONTENT_LENGTH   (void) const { return contentLength;    }
        class Text *CONTENT_TYPE     (void) const { return contentType;      }
        class Text *GATEWAY_INTERFACE(void) const { return gatewayInterface; }
        class Text *PATH             (void) const { return path;             }
        class Text *PATH_INFO        (void) const { return pathInfo;         }
        class Text *PATH_TRANSLATED  (void) const { return pathTranslated;   }
        class Text *QUERY_STRING     (void) const { return queryString;      }
        class Text *REMOTE_ADDR      (void) const { return remoteAddr;       }
        class Text *REMOTE_HOST      (void) const { return remoteHost;       }
        class Text *REMOTE_IDENT     (void) const { return remoteIdent;      }
        class Text *REMOTE_USER      (void) const { return remoteUser;       }
        class Text *REQUEST_METHOD   (void) const { return requestMethod;    }
        class Text *SCRIPT_NAME      (void) const { return scriptName;       }
        class Text *SERVER_NAME      (void) const { return serverName;       }
        class Text *SERVER_PORT      (void) const { return serverPort;       }
        class Text *SERVER_PROTOCOL  (void) const { return serverProtocol;   }
        class Text *SERVER_SOFTWARE  (void) const { return serverSoftware;   }
        
        class Text *authType;
        class Text *contentLength;
        class Text *contentType;
        class Text *gatewayInterface;
        class Text *path;
        class Text *pathInfo;
        class Text *pathTranslated;
        class Text *queryString;
        class Text *remoteAddr;
        class Text *remoteHost;
        class Text *remoteIdent;
        class Text *remoteUser;
        class Text *requestMethod;
        class Text *scriptName;
        class Text *serverName;
        class Text *serverPort;
        class Text *serverProtocol;
        class Text *serverSoftware;
    }; // class CGI
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_CGI_HPP
