#include "local.hpp"
#include <cstring>

//============================================================================
// Text()
//   creates blank object
//
NFTM::Text::Text(void) {
	isNull     = true;
	currLength = 0;
	maxLength  = 0;
	data       = 0;
}

//============================================================================
// Text(str)
//   creates object as a copy of str
//
NFTM::Text::Text(const char *str) {
    isNull = str ? false : true;
    
    if (isNull) {
        currLength = 0;
        maxLength  = 0;
        data       = new char[1];
        data[0]    = 0;
    } else {
        int length = (int)std::strlen(str);
        
        currLength = length;
        maxLength  = currLength;
        data       = new char[currLength + 1];
        
        std::strncpy(data, str, length);
        data[length] = 0;
    }
}

//============================================================================
// Text(str, int length)
//   creates object as a copy of str, up to length bytes
//
NFTM::Text::Text(const char *str, int length) {
    isNull = str ? false : true;
    
    if (isNull) {
        currLength = 0;
        maxLength  = 0;
        data       = new char[1];
        data[0]    = 0;
    } else {
        int actLength = (int)std::strlen(str);

        if (length < 0) {
            length = actLength;
        }

        if (actLength < length) {
            length = actLength;
        }

        currLength = length;
        maxLength  = currLength;
        data       = new char[currLength + 1];

        std::strncpy(data, str, length);
        data[length] = 0;
    }
}

//============================================================================
// Text(text)
//   creates object as a copy of text
//
NFTM::Text::Text(NFTM::Text *text) {
    isNull = (!text || text->IsNull()) ? true : false;
    
    if (isNull) {
        currLength = 0;
        maxLength  = 0;
        data       = new char[1];
        data[0]    = 0;
    } else {
        const char *str    = text->AsCString();
        int         length = (int)std::strlen(str);
        
        currLength = length;
        maxLength  = currLength;
        data       = new char[currLength + 1];
        
        std::strncpy(data, str, length);
        data[length] = 0;
    }
}

//============================================================================
// Text(text, int length)
//   creates object as a copy of text, up to length bytes
//
NFTM::Text::Text(NFTM::Text *text, int length) {
    isNull = (!text || text->IsNull()) ? true : false;

    if (isNull) {
        currLength = 0;
        maxLength  = 0;
        data       = new char[1];
        data[0]    = 0;
    } else {
        const char *str       = text->AsCString();
        int         actLength = (int)std::strlen(str);

        if (length < 0) {
            length = actLength;
        }

        if (actLength < length) {
            length = actLength;
        }

        currLength = length;
        maxLength  = currLength;
        data       = new char[currLength + 1];

        std::strncpy(data, str, length);
        data[length] = 0;
    }
}

