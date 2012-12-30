#include "local.hpp"
#include <stdlib.h>

//============================================================================
// GetEnv(defaultPath, defaultScriptName)
//   pulls CGI variables from environment
//
bool NFTM::CGI::GetEnv(const char *defaultPath, const char *defaultScriptName) {
	authType         = new NFTM::VarText("AUTH_TYPE"        , getenv("AUTH_TYPE"        ));
	contentLength    = new NFTM::VarText("CONTENT_LENGTH"   , getenv("CONTENT_LENGTH"   ));
	contentType      = new NFTM::VarText("CONTENT_TYPE"     , getenv("CONTENT_TYPE"     ));
	gatewayInterface = new NFTM::VarText("GATEWAY_INTERFACE", getenv("GATEWAY_INTERFACE"));
	path             = new NFTM::VarText("PATH"             , getenv("PATH"             ));
	pathInfo         = new NFTM::VarText("PATH_INFO"        , getenv("PATH_INFO"        ));
	pathTranslated   = new NFTM::VarText("PATH_TRANSLATED"  , getenv("PATH_TRANSLATED"  ));
	queryString      = new NFTM::VarText("QUERY_STRING"     , getenv("QUERY_STRING"     ));
	remoteAddr       = new NFTM::VarText("REMOTE_ADDR"      , getenv("REMOTE_ADDR"      ));
	remoteHost       = new NFTM::VarText("REMOTE_HOST"      , getenv("REMOTE_HOST"      ));
	remoteIdent      = new NFTM::VarText("REMOTE_IDENT"     , getenv("REMOTE_IDENT"     ));
	remoteUser       = new NFTM::VarText("REMOTE_USER"      , getenv("REMOTE_USER"      ));
	requestMethod    = new NFTM::VarText("REQUEST_METHOD"   , getenv("REQUEST_METHOD"   ));
	scriptName       = new NFTM::VarText("SCRIPT_NAME"      , getenv("SCRIPT_NAME"      ));
	serverName       = new NFTM::VarText("SERVER_NAME"      , getenv("SERVER_NAME"      ));
	serverPort       = new NFTM::VarText("SERVER_PORT"      , getenv("SERVER_PORT"      ));
	serverProtocol   = new NFTM::VarText("SERVER_PROTOCOL"  , getenv("SERVER_PROTOCOL"  ));
	serverSoftware   = new NFTM::VarText("SERVER_SOFTWARE"  , getenv("SERVER_SOFTWARE"  ));

	// apply default values
	if (pathInfo->IsNull()) {
        delete pathInfo;
        pathInfo = new NFTM::VarText("PATH_INFO", defaultPath);
	}

	if (scriptName->IsNull()) {
        delete scriptName;
        scriptName = new NFTM::VarText("SCRIPT_NAME", defaultScriptName);
	}

	return true;
}

