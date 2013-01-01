#include "local.hpp"
#include <stdlib.h>

//============================================================================
// GetEnv(defaultPath, defaultScriptName)
//   pulls CGI variables from environment
//
bool NFTM::CGI::GetEnv(const char *defaultPath, const char *defaultScriptName) {
	authType         = new NFTM::Text(getenv("AUTH_TYPE"        ));
	contentLength    = new NFTM::Text(getenv("CONTENT_LENGTH"   ));
	contentType      = new NFTM::Text(getenv("CONTENT_TYPE"     ));
	gatewayInterface = new NFTM::Text(getenv("GATEWAY_INTERFACE"));
	path             = new NFTM::Text(getenv("PATH"             ));
	pathInfo         = new NFTM::Text(getenv("PATH_INFO"        ));
	pathTranslated   = new NFTM::Text(getenv("PATH_TRANSLATED"  ));
	queryString      = new NFTM::Text(getenv("QUERY_STRING"     ));
	remoteAddr       = new NFTM::Text(getenv("REMOTE_ADDR"      ));
	remoteHost       = new NFTM::Text(getenv("REMOTE_HOST"      ));
	remoteIdent      = new NFTM::Text(getenv("REMOTE_IDENT"     ));
	remoteUser       = new NFTM::Text(getenv("REMOTE_USER"      ));
	requestMethod    = new NFTM::Text(getenv("REQUEST_METHOD"   ));
	scriptName       = new NFTM::Text(getenv("SCRIPT_NAME"      ));
	serverName       = new NFTM::Text(getenv("SERVER_NAME"      ));
	serverPort       = new NFTM::Text(getenv("SERVER_PORT"      ));
	serverProtocol   = new NFTM::Text(getenv("SERVER_PROTOCOL"  ));
	serverSoftware   = new NFTM::Text(getenv("SERVER_SOFTWARE"  ));

	// apply default values
	if (pathInfo->IsNull()) {
        delete pathInfo;
        pathInfo = new NFTM::Text(defaultPath);
	}

	if (scriptName->IsNull()) {
        delete scriptName;
        scriptName = new NFTM::Text(defaultScriptName);
	}

	return true;
}

