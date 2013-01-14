/**************************************************************************
 *
 * Copyright (c) 2013 Michael D Henderson
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************
 * This file is part of StaticCMS (http://github.com/quoha/StaticCMS).
 *************************************************************************/

#include "SearchPath.h"
#include <stdio.h>
#include <cstring>
#include <sys/stat.h>

struct StaticCMS::PathStack {
    struct PathStack  *prev;
    struct PathStack  *next;
    const char        *path;

    PathStack(const char *newPath) {
        prev = 0;
        next = 0;
        
        char *s = new char[std::strlen(newPath ? newPath : "") + 1];
        std::strcpy(s, newPath ? newPath : "");
        path = s;
    }
    ~PathStack() {
        delete [] path;
    }
};

StaticCMS::SearchPath::SearchPath(void) {
    top = 0;
}

StaticCMS::SearchPath::~SearchPath() {
    while (top) {
        struct PathStack *prev = top->prev;
        delete top;
        top = prev;
    }
}

bool StaticCMS::SearchPath::AddPath(const char *path) {
    // splice the new node into the stack
    //
    if (!top) {
        top = new struct PathStack(path);
    } else {
        top->next = new struct PathStack(path);
        top->next->prev = top;
        top = top->next;
    }

    return true;
}

const char *StaticCMS::SearchPath::FindFile(const char *fileName) {
    struct PathStack *c = top;

    while (c) {
        char buf[1024];
        snprintf(buf, 1024, "%s%s", c->path, fileName);
        buf[1023] = 0;

        printf(" srch:\tlooking for %s\n", buf);

        struct stat sb;
        if (stat(buf, &sb) == 0 && S_ISREG(sb.st_mode)) {
            // found file, return full path to it
            //
            printf(" srch:\tfound       %s\n", buf);
            return std::strcpy(new char[std::strlen(buf) + 1], buf);
        }
        c = c->prev;
    }

    // did not find the file in the search path
    //
    return 0;
}
