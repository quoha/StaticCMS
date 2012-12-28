#include "local.hpp"
#include "../Stream.hpp"

//============================================================================
// DumpEnv(fp)
//   displays CGI settings
//
void NFTM::CGI::DumpEnv(NFTM::OutputStream *os) const {
	os->LogVar(authType         );
	os->LogVar(contentLength    );
	os->LogVar(contentType      );
	os->LogVar(gatewayInterface );
	os->LogVar(path             );
	os->LogVar(pathInfo         );
	os->LogVar(pathTranslated   );
	os->LogVar(queryString      );
	os->LogVar(remoteAddr       );
	os->LogVar(remoteHost       );
	os->LogVar(remoteIdent      );
	os->LogVar(remoteUser       );
	os->LogVar(requestMethod    );
	os->LogVar(scriptName       );
	os->LogVar(serverName       );
	os->LogVar(serverPort       );
	os->LogVar(serverProtocol   );
	os->LogVar(serverSoftware   );
}
