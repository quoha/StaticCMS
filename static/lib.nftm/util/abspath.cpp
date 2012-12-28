#include "local.hpp"

//============================================================================
// AbsPath(path)
//
// Change // to // and remove x/.. from path
//
char *NFTM::AbsPath(char *path) {
	bool  leadingSlash = path[0] == '/' ? true : false;
	char *startOfPath  = path;
	char *endOfPath    = path;

	//
	// find the end of the path. at the same time, remove all slashes
	// from the path
	//
	while (*endOfPath) {
		if (*endOfPath == '/') {
			*endOfPath = 0;
		}
		endOfPath++;
	}

	//
	// scan the path for a directories named . and remove them
	//
	path = startOfPath;
	while (path < endOfPath) {
		//
		// skip to next directory name
		//
		while (path < endOfPath && *path == 0) {
			path++;
		}

		if (*path == '.' && *(path + 1) == 0) {
			*(path) = 0;
		}

		//
		// skip to end of directory name
		//
		while (path < endOfPath && *path) {
			path++;
		}
	}

	//
	// scan the path for directories named .. and remove them and their parent
	//
	path = startOfPath;
	while (path < endOfPath) {
		//
		// skip to start of directory name
		//
		while (path < endOfPath && *path == 0) {
			path++;
		}

		if (*path == '.' && *(path + 1) == '.' && *(path + 2) == 0) {
			//
			// back up, find the start of the parent and remove it
			//
			char *mark = path - 1;
			while (mark >= startOfPath && *mark == 0) {
				mark--;
			}
			while (mark >= startOfPath && *mark) {
				mark--;

			}
			while (mark < path) {
				*(mark++) = 0;
			}

			//
			// remove the child
			//
			while (*path) {
				*(path++) = 0;
			}

		} else {
			//
			// skip to end of directory name
			//
			while (path < endOfPath && *path) {
				path++;
			}
		}
	}

	//
	// coallesce what remains into the new path
	//
	char *tgt = startOfPath;
	char *src = startOfPath;

	while (src < endOfPath) {
		//
		// skip to start of directory name in path
		//
		while (src < endOfPath && *src == 0) {
			src++;
		}

		//
		// only put in leading slash if we had one
		// in the original path.
		//
		if (tgt == startOfPath) {
			if (leadingSlash) {
				*(tgt++) = '/';
			}
		} else {
			*(tgt++) = '/';
		}

		//
		// copy the entire directory name to the path
		//
		while (src < endOfPath && *src) {
			*(tgt++) = *(src++);
		}
		*tgt = 0;
	}

	return startOfPath;
}

#if 0
//============================================================================
// AbsPath(path)
//
// Change // to // and remove x/.. from path
//
char *AAbsPath(char *path) {
printf("AbsPath(%s)\n", path);
	int numberOfChanges = 0;
	do {
		//
		// change all // to /
		//
		char *s = path;
		while (*s) {
			if (*s == '/' && *(s+1) == '/') {
				char *p = s;
				char *q = s;
				while (*q == '/') {
					q++;
				}
				while (*q) {
					*(p++) = *(q++);
				}
				*p = 0;
			}
			s++;
		}

		s = path;
		numberOfChanges = 0;

		char *dir[maxLevels + 1];

		for (int idx = 0; idx < maxLevels; idx++) {
			// skip leading /
			while (*s && *s == '/') {
				*(s++) = 0;
			}
			dir[idx] = *s ? s : 0;
			while (*s && *s != '/') {
				s++;
			}
		}
		dir[maxLevels] = 0;

		//
		// remove dir/..
		//
		int idx = 0;
		while (idx < maxLevels) {
			int idParent = idx;
			int idChild  = -1;
			for (int idy = idParent + 1; idy < maxLevels; idy++) {
				if (dir[idy]) {
					idChild = idy;
					break;
				}
			}
			if (idChild > idParent && (dir[idChild][0] == '.' && dir[idChild][1] == '.' && dir[idChild][2] == 0)) {
				numberOfChanges++;
				dir[idParent] = 0;
				dir[idChild ] = 0;
				idx--;
				if (idx < 0) {
					idx = 0;
				}
			} else {
				idx++;
			}
		}

		// now copy dir back into path
		char *tgt = path;
		for (int idx = 0; idx < maxLevels; idx++) {
			char *src = dir[idx];
			if (src) {
				if (idx > 0) {
					*(tgt++) = '/';
				}
				while (*src) {
					*(tgt++) = *(src++);
					//src++;
				}
			}
		}
		if (tgt == path) {
			*(tgt++) = '/';
		}
		*tgt = 0;

		if (!numberOfChanges) {
			break;
		}
	} while (numberOfChanges > 0);

	return path;
}
#endif
