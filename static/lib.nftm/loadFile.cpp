#include "Util.hpp"

#include <stdio.h>
#include <sys/stat.h>

//---------------------------------------------------------------------------
// LoadFile(fileName)
//
char *NFTM::LoadFile(const char *fileName, bool trimTrailingNewLine) {
    char *data = 0;
    
    struct stat statBuf;
    if (fileName && *fileName && stat(fileName, &statBuf) == 0) {
        data = new char[statBuf.st_size + 1];
        
        FILE *fp = fopen(fileName, "r");
        if (!fp) {
            delete [] data;
            data = 0;
            return data;
        } else if (fread(data, statBuf.st_size, 1, fp) != 1) {
            delete [] data;
            data = 0;
            fclose(fp);
            return data;
        }

        fclose(fp);
        
        // get rid of one trailing new-line
        //
        if (trimTrailingNewLine && statBuf.st_size > 0 && data[statBuf.st_size - 1] == '\n') {
            data[statBuf.st_size - 1] = 0;
        }
        
        data[statBuf.st_size] = 0;
    }

    return data;
}
