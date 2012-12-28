#include "local.hpp"
#include <stdio.h>
#include <cstring>
#include <sys/stat.h>

//============================================================================
// FromFile(fileName, forceNewLine)
//   reads file into data
// fileName      name of file to read data from
// forceNewLine  if non-zero, ensure that the buffer ends on a new-line
//
bool NFTM::Text::FromFile(const char *fileName, bool forceNewLine) {

	Release();

	struct stat statBuf;
	if (stat(fileName, &statBuf) != 0) {
perror(fileName);
		return false;
	}

	// allocate enough space for the file and
	// the new line plus nil terminator
	//
	char *buffer = new char[statBuf.st_size + 2];

	// only read in the file if it is not empty
	//
	if (statBuf.st_size > 0) {
		bool  foundError = false;
		FILE *fp         = fopen(fileName, "r");
		if (!fp || fread(buffer, statBuf.st_size, 1, fp) != 1) {
perror(fileName);
			foundError = true;
		}
		fclose(fp);

		if (foundError) {
			// error reading. bail.
			//
			delete [] buffer;
			return false;
		}
	}

	isNull     = false;
	currLength = (int)statBuf.st_size;
	maxLength  = currLength + (forceNewLine ? 1 : 0);
	data       = buffer;

	// force a new line only if we are asked and the last character
	// in the buffer is not already a new line
	//
	if (forceNewLine && (currLength == 0 || buffer[currLength - 1] != '\n')) {
		buffer[currLength++] = '\n';
	}

	// always make sure we are nil-terminated
	//
	buffer[currLength] = 0;

	return true;
}
