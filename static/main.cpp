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

// four things per terence parr
//  1. attribute reference
//  2. conditional template inclusion
//  3. recursive template references
//  4. "map" operator

#include "local.hpp"
#include "lib.nftm/Stack.hpp"
#include "lib.nftm/SymbolTable.hpp"
#include "ArticleController.hpp"
#include "Model.h"
#include "SearchPath.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    StaticCMS::Model      model;
    StaticCMS::SearchPath searchPath;

    const char *outputFile = 0;
    const char *viewFile   = 0;

	stdout = stderr;

	for (int idx = 1; idx < argc; idx++) {
		char *opt = argv[idx];
		char *val = opt;
		while (*val && *val != '=') {
			val++;
		}
		if (*val) {
			*(val++) = 0;
		} else {
			val = 0;
		}

        // work through the list of options
        //
        if (StaticCMS::OptIs(opt, "help")) {
            printf("usage:\t%s ....\n", argv[0]);
            return 2;
        } else if (StaticCMS::OptIs(opt, "model-file") && val && *val) {
            // load the model from the file
            //
            printf(" info:\t%-20s == '%s'\n", "modelFile", val);
            const char *modelFile = searchPath.FindFile(val);
            if (!modelFile) {
                printf("\nerror:\tcan't find model file in search path\n\n");
                return 2;
            }
            printf(" info:\t%-20s == '%s'\n", "modelFile", modelFile);
            if (!model.AddVariablesFromFile(modelFile)) {
                printf("\nerror:\tunable to load model from file\n");
                printf(" info:\t%-20s == '%s'\n", "modelFile", modelFile);
                return 2;
            }
            delete [] modelFile;
        } else if (StaticCMS::OptIs(opt, "output-file") && val && *val) {
            outputFile = val;
        } else if (StaticCMS::OptIs(opt, "search-path") && val && *val) {
            // add search path
            //
            searchPath.AddPath(val);
        } else if (StaticCMS::OptIs(opt, "view-file") && val && *val) {
            viewFile = val;
		} else if (StaticCMS::OptIs(opt, "variable") && val && *val) {
        } else {
            printf("\nerror:\tinvalid option '%s%s%s'\n", opt, val ? "=" : "", val ? val : "");
			printf("\ttry --help if you're stuck\n\n");
			return 2;
		}
	}

    if (!outputFile) {
        printf(" warn:\toutput file not specified, will not create anything\n");
    }
    if (!viewFile) {
        printf("\nerror:\tyou must specify a view file to load\n\n");
        return 2;
    }

    printf(" info:\t%-20s == '%s'\n", "outputFile", outputFile);
    printf(" info:\t%-20s == '%s'\n", "viewFile", viewFile);

	return 0;
}
