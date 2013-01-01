#include "local.hpp"

//============================================================================
// ExportToSymTab(symtab)
//
bool NFTM::CGI::ExportToSymTab(NFTM::SymbolTable *symtab) {
    if (!symtab) {
        return false;
    }

	symtab->Add("AUTH_TYPE"        , authType        );
	symtab->Add("CONTENT_LENGTH"   , contentLength   );
	symtab->Add("CONTENT_TYPE"     , contentType     );
	symtab->Add("GATEWAY_INTERFACE", gatewayInterface);
	symtab->Add("PATH"             , path            );
	symtab->Add("PATH_INFO"        , pathInfo        );
	symtab->Add("PATH_TRANSLATED"  , pathTranslated  );
	symtab->Add("QUERY_STRING"     , queryString     );
	symtab->Add("REMOTE_ADDR"      , remoteAddr      );
	symtab->Add("REMOTE_HOST"      , remoteHost      );
	symtab->Add("REMOTE_IDENT"     , remoteIdent     );
	symtab->Add("REMOTE_USER"      , remoteUser      );
	symtab->Add("REQUEST_METHOD"   , requestMethod   );
	symtab->Add("SCRIPT_NAME"      , scriptName      );
	symtab->Add("SERVER_NAME"      , serverName      );
	symtab->Add("SERVER_PORT"      , serverPort      );
	symtab->Add("SERVER_PROTOCOL"  , serverProtocol  );
	symtab->Add("SERVER_SOFTWARE"  , serverSoftware  );
    
    return true;
}
