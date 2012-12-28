#include "local.hpp"

NFTM::Variable *NFTM::CGI::AUTH_TYPE        (void) const { return authType;         }
NFTM::Variable *NFTM::CGI::CONTENT_LENGTH   (void) const { return contentLength;    }
NFTM::Variable *NFTM::CGI::CONTENT_TYPE     (void) const { return contentType;      }
NFTM::Variable *NFTM::CGI::GATEWAY_INTERFACE(void) const { return gatewayInterface; }
NFTM::Variable *NFTM::CGI::PATH             (void) const { return path;             }
NFTM::Variable *NFTM::CGI::PATH_INFO        (void) const { return pathInfo;         }
NFTM::Variable *NFTM::CGI::PATH_TRANSLATED  (void) const { return pathTranslated;   }
NFTM::Variable *NFTM::CGI::QUERY_STRING     (void) const { return queryString;      }
NFTM::Variable *NFTM::CGI::REMOTE_ADDR      (void) const { return remoteAddr;       }
NFTM::Variable *NFTM::CGI::REMOTE_HOST      (void) const { return remoteHost;       }
NFTM::Variable *NFTM::CGI::REMOTE_IDENT     (void) const { return remoteIdent;      }
NFTM::Variable *NFTM::CGI::REMOTE_USER      (void) const { return remoteUser;       }
NFTM::Variable *NFTM::CGI::REQUEST_METHOD   (void) const { return requestMethod;    }
NFTM::Variable *NFTM::CGI::SCRIPT_NAME      (void) const { return scriptName;       }
NFTM::Variable *NFTM::CGI::SERVER_NAME      (void) const { return serverName;       }
NFTM::Variable *NFTM::CGI::SERVER_PORT      (void) const { return serverPort;       }
NFTM::Variable *NFTM::CGI::SERVER_PROTOCOL  (void) const { return serverProtocol;   }
NFTM::Variable *NFTM::CGI::SERVER_SOFTWARE  (void) const { return serverSoftware;   }

