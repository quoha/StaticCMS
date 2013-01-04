#include "Text.hpp"
#include <stdio.h>
#include <cstring>
#include <sys/stat.h>

//============================================================================
// ~Text()
//   deletes object
//
NFTM::Text::~Text() {
	delete [] text;
    text = 0;
}

//============================================================================
// Text()
//   creates blank object
//
NFTM::Text::Text(void) {
	isNull     = true;
    isTainted  = false;
    text       = new char[1];
    text[0]    = 0;
}

//============================================================================
// Text(str)
//   creates object as a copy of str
//
NFTM::Text::Text(const char *str) {
    isNull    = str ? false : true;
    isTainted = false;

    if (isNull) {
        text    = new char[1];
        text[0] = 0;
    } else {
        int actLength = (int)std::strlen(str);
        text = new char[actLength + 1];
        std::strncpy(text, str, actLength);
        text[actLength] = 0;
    }
}

//============================================================================
// Text(str)
//   creates object as a copy of str
//
NFTM::Text::Text(const char *str1, const char *str2) {
    isNull    = (str1 || str2) ? false : true;
    isTainted = false;
    
    if (isNull) {
        text    = new char[1];
        text[0] = 0;
    } else {
        str1 = str1 ? str1 : "";
        str2 = str2 ? str2 : "";

        int actLength = (int)std::strlen(str1) + (int)std::strlen(str2);
        text = new char[actLength + 1];
        sprintf(text, "%s%s", str1, str2);
    }
}

//============================================================================
// Text(str, length)
//   creates object as a copy of str, up to length bytes
//
NFTM::Text::Text(const char *str, int length) {
    isNull    = str ? false : true;
    isTainted = false;
    
    if (isNull) {
        text    = new char[1];
        text[0] = 0;
    } else {
        int actLength = (int)std::strlen(str);
        
        if (length < 0) {
            length = actLength;
        } else if (actLength < length) {
            length = actLength;
        }
        
        text = new char[length + 1];
        std::strncpy(text, str, length);
        text[length] = 0;
    }
}

//============================================================================
// Text(text)
//   creates object as a copy of text
//
NFTM::Text::Text(NFTM::Text *text_) {
    isNull    = text_ ? text_->isNull    : true;
    isTainted = text_ ? text_->isTainted : false;

    if (isNull) {
        text    = new char[1];
        text[0] = 0;
    } else {
        int actLength = (int)std::strlen(text_->text);
        text = new char[actLength + 1];
        std::strncpy(text, text_->text, actLength);
        text[actLength] = 0;
    }
}

//============================================================================
// Text(text1, text2)
//   creates object as a concat of text1 and text2
//
NFTM::Text::Text(NFTM::Text *text1, NFTM::Text *text2) {
    isNull    = true;
    isTainted = false;

    if (text1) {
        if (!text1->isNull) {
            isNull = false;
        }
        if (text1->isTainted) {
            isTainted = true;
        }
    }
    if (text2) {
        if (!text2->isNull) {
            isNull = false;
        }
        if (text2->isTainted) {
            isTainted = true;
        }
    }

    if (isNull) {
        text    = new char[1];
        text[0] = 0;
    } else {
        const char *str1 = text1 ? text1->text : "";
        const char *str2 = text2 ? text2->text : "";
        
        int actLength = (int)std::strlen(str1) + (int)std::strlen(str2);
        text = new char[actLength + 1];
        sprintf(text, "%s%s", str1, str2);
    }
}

//============================================================================
// Text(text, length)
//   creates object as a copy of text, up to length bytes
//
NFTM::Text::Text(NFTM::Text *text_, int length) {
    isNull    = text_ ? text_->isNull    : true;
    isTainted = text_ ? text_->isTainted : false;
    
    if (isNull) {
        text    = new char[1];
        text[0] = 0;
    } else {
        int actLength = (int)std::strlen(text_->text);

        if (length < 0) {
            length = actLength;
        } else if (actLength < length) {
            length = actLength;
        }

        text = new char[length + 1];
        std::strncpy(text, text_->text, length);
        text[length] = 0;
    }
}

//============================================================================
// Text(fileName, forceNewLine, trimTrailingNewLine)
//   reads file into data
// fileName            name of file to read data from
// forceNewLine        if true, ensure that the buffer ends on a new-line
// trimTrailingNewLine if true, remove last new-line from file
//
// will leave text set to NULL and isNull set to TRUE if there are errors
//
NFTM::Text::Text(NFTM::Text *fileName_, bool forceNewLine, bool trimTrailingNewline) {
	isNull     = true;
    isTainted  = false;
    text       = 0;
    
    const char *fileName = fileName_ ? fileName_->text : "";
	struct stat statBuf;
	if (stat(fileName, &statBuf) == 0) {
        // allocate enough space for the file and
        // the new line plus nil terminator
        //
        int actLength       = (int)statBuf.st_size;
        text                = new char[actLength + 2];
        
        // set those two extra bytes to zero so that we don't forget to
        // do it later. they ensure that we end up nil-terminated.
        //
        text[actLength    ] = 0;
        text[actLength + 1] = 0;
        
        // only do the file read if it has data in it
        //
        if (actLength > 0) {
            FILE *fp = fopen(fileName, "r");
            if (!fp || fread(text, statBuf.st_size, 1, fp) != 1) {
                // delete text on any error
                //
                delete [] text;
                text = 0;
            }
            if (fp) {
                fclose(fp);
            }
        }
        
        // do the logic to force or trim trailing newline
        //
        if (text) {
            isNull = false;
            
            if (forceNewLine) {
                if (actLength == 0) {
                    text[0] = '\n';
                    text[1] = 0;
                } else if (text[actLength - 1] != '\n') {
                    text[actLength    ] = '\n';
                }
            } else if (trimTrailingNewline) {
                if (actLength > 0 && text[actLength - 1] != '\n') {
                    text[actLength - 1] = 0;
                }
            }
        }
    }
}

//============================================================================
// Equals(str)
//
// NOTE null never equals null
//
bool NFTM::Text::Equals(const char *str) const {
    if (isNull || !str || !text || std::strcmp(text, str) != 0) {
        return false;
    }

    return true;
}

//============================================================================
// PullText()
//
NFTM::Text *NFTM::Text::PullText(void) const {
    const char *startOfText = text;

    if (text) {
        const char *startOfVars  = std::strstr(text, "~~~\n");
        if (startOfVars == text) {
            startOfVars += 4;
            
            startOfText = std::strstr(startOfVars, "~~~\n");
            if (startOfText) {
                startOfText += 4;
            } else {
                startOfText = startOfVars;
            }
        }
    }
    
    return new Text(startOfText);
}

//============================================================================
// PullVariables()
//
NFTM::Text *NFTM::Text::PullVariables(void) const {
    if (text) {
        const char *startOfVars  = std::strstr(text, "~~~\n");
        if (startOfVars == text) {
            startOfVars += 4;

            const char *startOfText = std::strstr(startOfVars, "~~~\n");
            if (startOfText) {
                return new Text(startOfVars, (int)(startOfText - startOfVars));
            }
        }
    }

    // no variables
    //
    return new Text("");
}
