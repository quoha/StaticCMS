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
        
        class VarText *AUTH_TYPE        (void) const { return authType;         }
        class VarText *CONTENT_LENGTH   (void) const { return contentLength;    }
        class VarText *CONTENT_TYPE     (void) const { return contentType;      }
        class VarText *GATEWAY_INTERFACE(void) const { return gatewayInterface; }
        class VarText *PATH             (void) const { return path;             }
        class VarText *PATH_INFO        (void) const { return pathInfo;         }
        class VarText *PATH_TRANSLATED  (void) const { return pathTranslated;   }
        class VarText *QUERY_STRING     (void) const { return queryString;      }
        class VarText *REMOTE_ADDR      (void) const { return remoteAddr;       }
        class VarText *REMOTE_HOST      (void) const { return remoteHost;       }
        class VarText *REMOTE_IDENT     (void) const { return remoteIdent;      }
        class VarText *REMOTE_USER      (void) const { return remoteUser;       }
        class VarText *REQUEST_METHOD   (void) const { return requestMethod;    }
        class VarText *SCRIPT_NAME      (void) const { return scriptName;       }
        class VarText *SERVER_NAME      (void) const { return serverName;       }
        class VarText *SERVER_PORT      (void) const { return serverPort;       }
        class VarText *SERVER_PROTOCOL  (void) const { return serverProtocol;   }
        class VarText *SERVER_SOFTWARE  (void) const { return serverSoftware;   }
        
        class VarText *authType;
        class VarText *contentLength;
        class VarText *contentType;
        class VarText *gatewayInterface;
        class VarText *path;
        class VarText *pathInfo;
        class VarText *pathTranslated;
        class VarText *queryString;
        class VarText *remoteAddr;
        class VarText *remoteHost;
        class VarText *remoteIdent;
        class VarText *remoteUser;
        class VarText *requestMethod;
        class VarText *scriptName;
        class VarText *serverName;
        class VarText *serverPort;
        class VarText *serverProtocol;
        class VarText *serverSoftware;
    }; // class CGI
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_CGI_HPP
