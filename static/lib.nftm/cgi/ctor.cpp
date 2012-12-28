#include "local.hpp"

//============================================================================
// CGI(symtab, argv)
//   creates CGI environment
//
NFTM::CGI::CGI(void) {
	symtab           = 0;
	authType         = 0;
	contentLength    = 0;
	contentType      = 0;
	gatewayInterface = 0;
	path             = 0;
	pathInfo         = 0;
	pathTranslated   = 0;
	queryString      = 0;
	remoteAddr       = 0;
	remoteHost       = 0;
	remoteIdent      = 0;
	remoteUser       = 0;
	requestMethod    = 0;
	scriptName       = 0;
	serverName       = 0;
	serverPort       = 0;
	serverProtocol   = 0;
	serverSoftware   = 0;
}
