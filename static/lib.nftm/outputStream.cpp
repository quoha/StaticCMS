#include "Stream.hpp"
#include "Text.hpp"
#include "Variable.hpp"
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

//============================================================================
// OutputStream(fileName)
//
NFTM::OutputStream::OutputStream(const char *fileName_) {
	data     = 0;
	errmsg   = 0;
    fileName = new NFTM::Text(fileName_);
	Open(fileName);
}

//============================================================================
// OutputStream(fileName)
//
NFTM::OutputStream::OutputStream(NFTM::Text *fileName_) {
	data     = 0;
	errmsg   = 0;
    fileName = new NFTM::Text(fileName_);
	Open(fileName);
}

//============================================================================
//
NFTM::OutputStream::~OutputStream() {
	Close();

    delete errmsg;
    errmsg = 0;
    delete fileName;
    fileName = 0;
}

//============================================================================
// Close()
//
bool NFTM::OutputStream::Close(void) {
	if (data) {
		fflush((FILE *)data);
		if (data != stderr && data != stdout) {
			fclose((FILE *)data);
		}
	}
    
	data = 0;
    
    delete errmsg;
    errmsg = 0;
    
	return true;
}

//============================================================================
// Flush()
//
bool NFTM::OutputStream::Flush(void) {
	if (data) {
		fflush((FILE *)data);
	}
    
	return true;
}

//============================================================================
// LogVar(var)
//
bool NFTM::OutputStream::LogVar(NFTM::Variable *variable) {
	if (!data) {
        return false;
    }
    
    FILE *fp = (FILE *)(data);
    
    if (!variable) {
        fprintf(fp, "%-25s == %s\n", "invalidPointer", "**null pointer**");
    } else if (variable->IsBoolean()) {
        fprintf(fp, "%-25s == %s\n", variable->Name(), variable->u.boolean ? "true" : "false");
    } else if (variable->IsFunction()) {
        fprintf(fp, "%-25s == %s\n", variable->Name(), "**function**");;
    } else if (variable->IsNull()) {
        fprintf(fp, "%-25s == %s\n", variable->Name(), "null");
    } else if (variable->IsStack()) {
        fprintf(fp, "%-25s == %s\n", variable->Name(), "**stack**");
    } else if (variable->IsText()) {
        fprintf(fp, "%-25s == '%s'\n", variable->Name(), variable->u.text->text);
    } else {
        fprintf(fp, "%-25s == %s (%d)\n", variable->Name(), "**unknown type**", variable->kind);
    }
    
    return true;
}

//============================================================================
// Open(fileName)
//
bool NFTM::OutputStream::Open(NFTM::Text *fileName_) {
    delete errmsg;
	errmsg = 0;
    
	if (data) {
		Close();
	}
    
    if (fileName_) {
        if (fileName_->Equals("-")) {
            data = stdout;
        } else if (fileName_->Equals("null")) {
            data = NULL;
        } else if (fileName_->Equals("stderr")) {
            data = stderr;
        } else if (fileName_->Equals("stdout")) {
            data = stdout;
        } else {
            data = fopen(fileName_->text, "w");
            if (!data) {
                errmsg = new NFTM::Text(strerror(errno));
            }
        }
    }
    
	return data ? true : false;
}

//============================================================================
// Redirect(fileName)
//
bool NFTM::OutputStream::Redirect(NFTM::Text *fileName_) {
	if (data) {
		Close();
	}
	Open(fileName_);
    return true;
}

//============================================================================
// Write(fmt, ...)
//
bool NFTM::OutputStream::Write(const char *fmt, ...) {
	if (!data) {
		return false;
	}
    
	if (fmt && *fmt) {
		va_list ap;
		va_start(ap, fmt);
		vfprintf((FILE *)data, fmt, ap);
		va_end(ap);
	}
    
	return true;
}

//============================================================================
// Write(fmt, ...)
//
bool NFTM::OutputStream::Write(NFTM::Text *text) {
	if (!data) {
		return false;
	}

	if (text && text->text && text->text[0]) {
        fprintf((FILE *)data, "%s", text->text);
	}
    
	return true;
}
