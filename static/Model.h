//
//  Model.h
//  static
//
//  Created by Michael Henderson on 1/13/13.
//  Copyright (c) 2013 Michael Henderson. All rights reserved.
//

#ifndef __static__Model__
#define __static__Model__

#include "Dictionary.h"

namespace StaticCMS {
    
    class Model {
    public:
        Model(void);
        ~Model();
        
        bool AddVariable(const char *name, const char *value);
        bool AddVariablesFromFile(const char *fileName);
        bool AddVariablesFromString(char *string);
        void Dump(void);
        
        const char *GetVariable(const char *name);

    private:
        Dictionary dictionary;
    }; // class Model
    
} // namespace StaticCMS

#endif /* defined(__static__Model__) */
