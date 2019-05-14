//
//  codeGen.hpp
//  P4
//
//  Created by Eric Goodwin on 5/5/19.
//  Copyright © 2019 umsl. All rights reserved.
//

#ifndef codeGen_h
#define codeGen_h

#include <stdio.h>
#include <vector>
#include <string.h>
#include "parser.h"
#include "node.h"


extern FILE *outFile;
extern vector<string> globalContainer;

class CodeGen {
    
public:
    CodeGen();
    void Run(node* tree);
    
private:
    void traverseTree(node *tree, int depth);
    void print2Target(string command, string token);
    string nextTempVariable();
    bool verify(string variable);
    string nextLabel();
    
};


#endif /* statSem_h */
