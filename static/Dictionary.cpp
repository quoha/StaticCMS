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

#include "Dictionary.h"
#include <cstring>

StaticCMS::Dictionary::Dictionary(void) {
    for (int idx = 0; idx < hashSize; idx++) {
        hash[idx] = 0;
    }
}

StaticCMS::Dictionary::~Dictionary() {
    //
}

const char *StaticCMS::Dictionary::Entry(const char *key) const {
    key = key ? key : "";

    unsigned int hashValue = Hash(key);

	Bucket *b = hash[hashValue % hashSize];

	while (b) {
		if (b->hashValue == hashValue && std::strcmp(key, b->key) == 0) {
            return b->value;
		}
		b = b->next;
	}

    return 0;
}

bool StaticCMS::Dictionary::Entry(const char *key, const char *value) {
    key   = key   ? key   : "";
    value = value ? value : "";

	Bucket *b = new Bucket();

	b->hashValue         = Hash(key);
    b->key               = std::strcpy(new char[std::strlen(key  ) + 1], key  );
    b->value             = std::strcpy(new char[std::strlen(value) + 1], value);
    b->prev              = 0;
	b->next              = hash[b->hashValue % hashSize];
    if (b->next) {
        b->next->prev = b;
    }
    
	hash[b->hashValue % hashSize] = b;
    
	return true;
}

unsigned int StaticCMS::Dictionary::Hash(const char *key) const {
	unsigned int djbHash = 0;

    if (key) {
        while (*key) {
            djbHash = djbHash * 32 + djbHash + *(key++);
        }
    }

	return djbHash;
}
