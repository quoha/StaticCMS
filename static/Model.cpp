/**************************************************************************
 *
 * Copyright (c) 2013 Michael D Henderson
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
 * OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************
 * This file is part of StaticCMS (http://github.com/quoha/StaticCMS).
 *************************************************************************/

#include "Model.h"
#include "lib.nftm/Util.hpp"
#include <stdio.h>
#include <cstring>
#include <ctype.h>

StaticCMS::Model::Model(void) {
    //
}

StaticCMS::Model::~Model() {
    //
}

bool StaticCMS::Model::AddVariablesFromFile(const char *fileName) {
    char *data = LoadFile(fileName);
    if (!data) {
		perror(fileName);
        return false;
	}

    printf("---------\n%s\n-----------------\n", data);
    
    char *articleText = 0;

    if (std::strncmp(data, "<@<@>@>\n", 8) == 0) {
        data[0] = 0;
        articleText = data + 8;
    } else {
        char *separator = std::strstr(data, "\n<@<@>@>\n");
        if (separator) {
            *separator = 0;
            articleText = separator + 9;
        }
    }

    if (!AddVariablesFromString(data)) {
        delete [] data;
        return false;
    }

    if (!AddVariable("articleText", articleText)) {
        delete [] data;
        return false;
    }

    delete [] data;

    return true;
}

bool StaticCMS::Model::AddVariable(const char *name, const char *value) {
    return dictionary.Entry(name, value);
}

//
// format is name value
//
bool StaticCMS::Model::AddVariablesFromString(char *data) {
    // process one line at a time
    while (*data) {
        char *lineStart = data;
        while (*data && *data != '\n') {
            data++;
        }
        if (*data) {
            *(data++) = 0;
        }

        char *name = lineStart;
        while (*name && isspace(*name)) {
            *(name++) = 0;
        }

        char *value = name;
        while (*value && !isspace(*value)) {
            value++;
        }
        while (*value && isspace(*value)) {
            *(value++) = 0;
        }

        if (*name) {
            if (!AddVariable(name, value)) {
                return false;
            }
        }
    }

    return true;
}

const char *StaticCMS::Model::GetVariable(const char *name) {
    return dictionary.Entry(name);
}
