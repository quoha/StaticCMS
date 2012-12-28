#include "local.hpp"
#include <stdlib.h>

//============================================================================
// GetEnv(defaultPath, defaultScriptName)
//   pulls CGI variables from environment
//
bool NFTM::CGI::GetEnv(const char *defaultPath, const char *defaultScriptName) {
	authType         = new NFTM::Variable("AUTH_TYPE"        , getenv("AUTH_TYPE"        ));
	contentLength    = new NFTM::Variable("CONTENT_LENGTH"   , getenv("CONTENT_LENGTH"   ));
	contentType      = new NFTM::Variable("CONTENT_TYPE"     , getenv("CONTENT_TYPE"     ));
	gatewayInterface = new NFTM::Variable("GATEWAY_INTERFACE", getenv("GATEWAY_INTERFACE"));
	path             = new NFTM::Variable("PATH"             , getenv("PATH"             ));
	pathInfo         = new NFTM::Variable("PATH_INFO"        , getenv("PATH_INFO"        ));
	pathTranslated   = new NFTM::Variable("PATH_TRANSLATED"  , getenv("PATH_TRANSLATED"  ));
	queryString      = new NFTM::Variable("QUERY_STRING"     , getenv("QUERY_STRING"     ));
	remoteAddr       = new NFTM::Variable("REMOTE_ADDR"      , getenv("REMOTE_ADDR"      ));
	remoteHost       = new NFTM::Variable("REMOTE_HOST"      , getenv("REMOTE_HOST"      ));
	remoteIdent      = new NFTM::Variable("REMOTE_IDENT"     , getenv("REMOTE_IDENT"     ));
	remoteUser       = new NFTM::Variable("REMOTE_USER"      , getenv("REMOTE_USER"      ));
	requestMethod    = new NFTM::Variable("REQUEST_METHOD"   , getenv("REQUEST_METHOD"   ));
	scriptName       = new NFTM::Variable("SCRIPT_NAME"      , getenv("SCRIPT_NAME"      ));
	serverName       = new NFTM::Variable("SERVER_NAME"      , getenv("SERVER_NAME"      ));
	serverPort       = new NFTM::Variable("SERVER_PORT"      , getenv("SERVER_PORT"      ));
	serverProtocol   = new NFTM::Variable("SERVER_PROTOCOL"  , getenv("SERVER_PROTOCOL"  ));
	serverSoftware   = new NFTM::Variable("SERVER_SOFTWARE"  , getenv("SERVER_SOFTWARE"  ));

	// apply default values
	if (pathInfo->IsNull()) {
		pathInfo->Value(defaultPath);
	}

	if (scriptName->IsNull()) {
		scriptName->Value(defaultScriptName);
	}

	return true;
}

