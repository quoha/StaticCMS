#include "local.hpp"

//============================================================================
// RequestToPath()
//   convert the request into path elements
//   no matter what, argv[0] should always be /
//
void NFTM::Request::RequestToPath(void) {
    static char loneSlash[2] = {'/', 0};

	if (argv) {
		return;
	}

	// count the /
	//
	int   numberOfSlashes = 0;
	char *s = request;
	while (*s) {
		if (*(s++) == '/') {
			numberOfSlashes++;
		}
	}

	// create storage for them. the "+3" allows for a null
	// pointer to terminate the list as well as for the possibility
	// that the request does not start or end with a slash.
	//
	argv = new char *[numberOfSlashes + 3];

    // no matter what, argv[0] should be /
    //
    int idx = 0;
    argv[idx++] = loneSlash;

    // don't put that leading slash in there twice
    //
    s = request;
    while (*s && *s == '/') {
        *(s++) = 0;
    }

	// assign the remaining path elements to argv
	//
	while (*s) {
		while (*s == '/') {
			*(s++) = 0;
		}

		argv[idx++] = s;

		while (*s && *s != '/') {
			s++;
		}
	}

    // null terminate the list to make life simpler
    //
	argv[idx] = 0;
}
