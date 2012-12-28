#include "local.hpp"

const char *NFTM::CGI::AUTH_TYPE        (void) const { return authType->Value();         }
const char *NFTM::CGI::CONTENT_LENGTH   (void) const { return contentLength->Value();    }
const char *NFTM::CGI::CONTENT_TYPE     (void) const { return contentType->Value();      }
const char *NFTM::CGI::GATEWAY_INTERFACE(void) const { return gatewayInterface->Value(); }
const char *NFTM::CGI::PATH             (void) const { return path->Value();             }
const char *NFTM::CGI::PATH_INFO        (void) const { return pathInfo->Value();         }
const char *NFTM::CGI::PATH_TRANSLATED  (void) const { return pathTranslated->Value();   }
const char *NFTM::CGI::QUERY_STRING     (void) const { return queryString->Value();      }
const char *NFTM::CGI::REMOTE_ADDR      (void) const { return remoteAddr->Value();       }
const char *NFTM::CGI::REMOTE_HOST      (void) const { return remoteHost->Value();       }
const char *NFTM::CGI::REMOTE_IDENT     (void) const { return remoteIdent->Value();      }
const char *NFTM::CGI::REMOTE_USER      (void) const { return remoteUser->Value();       }
const char *NFTM::CGI::REQUEST_METHOD   (void) const { return requestMethod->Value();    }
const char *NFTM::CGI::SCRIPT_NAME      (void) const { return scriptName->Value();       }
const char *NFTM::CGI::SERVER_NAME      (void) const { return serverName->Value();       }
const char *NFTM::CGI::SERVER_PORT      (void) const { return serverPort->Value();       }
const char *NFTM::CGI::SERVER_PROTOCOL  (void) const { return serverProtocol->Value();   }
const char *NFTM::CGI::SERVER_SOFTWARE  (void) const { return serverSoftware->Value();   }

