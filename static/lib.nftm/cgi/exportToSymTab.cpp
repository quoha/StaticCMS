#include "local.hpp"

//============================================================================
// ExportToSymTab(symtab)
//
bool NFTM::CGI::ExportToSymTab(NFTM::SymbolTable *symtab_) {
	symtab           = symtab_;
    if (!symtab) {
        return false;
    }

	symtab->Add(authType        );
	symtab->Add(contentLength   );
	symtab->Add(contentType     );
	symtab->Add(gatewayInterface);
	symtab->Add(path            );
	symtab->Add(pathInfo        );
	symtab->Add(pathTranslated  );
	symtab->Add(queryString     );
	symtab->Add(remoteAddr      );
	symtab->Add(remoteHost      );
	symtab->Add(remoteIdent     );
	symtab->Add(remoteUser      );
	symtab->Add(requestMethod   );
	symtab->Add(scriptName      );
	symtab->Add(serverName      );
	symtab->Add(serverPort      );
	symtab->Add(serverProtocol  );
	symtab->Add(serverSoftware  );
    
    return true;
}
