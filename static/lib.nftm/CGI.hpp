#ifndef   NFTM_static_src_bin_static_CGI_HPP
#define   NFTM_static_src_bin_static_CGI_HPP

namespace NFTM {

class CGI {
public:
	CGI(void);
	~CGI();

    bool            AddArgs(char **argv);
	void            DumpEnv(class OutputStream *os) const;
    bool            ExportToSymTab(class SymbolTable *symtab);
	bool            GetEnv(const char *defaultPath, const char *defaultScriptName);
	class Variable *GetVar(const char *var);
	bool            SetVar(const char *var, const char *val);

	const char *AUTH_TYPE        (void) const;
	const char *CONTENT_LENGTH   (void) const;
	const char *CONTENT_TYPE     (void) const;
	const char *GATEWAY_INTERFACE(void) const;
	const char *PATH             (void) const;
	const char *PATH_INFO        (void) const;
	const char *PATH_TRANSLATED  (void) const;
	const char *QUERY_STRING     (void) const;
	const char *REMOTE_ADDR      (void) const;
	const char *REMOTE_HOST      (void) const;
	const char *REMOTE_IDENT     (void) const;
	const char *REMOTE_USER      (void) const;
	const char *REQUEST_METHOD   (void) const;
	const char *SCRIPT_NAME      (void) const;
	const char *SERVER_NAME      (void) const;
	const char *SERVER_PORT      (void) const;
	const char *SERVER_PROTOCOL  (void) const;
	const char *SERVER_SOFTWARE  (void) const;

	class SymbolTable *symtab;

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
