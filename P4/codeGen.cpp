//
//  codeGen.cpp
//  P4
//
//  Created by Eric Goodwin on 5/5/19.
//  Copyright © 2019 umsl. All rights reserved.
//

#include "codeGen.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "statSem.h"
#include "node.h"
#include "token.h"


const int DEVMODE = 1;


//reference https://www.geeksforgeeks.org/vector-in-cpp-stl/


using namespace std;

vector<string> globalContainer;

CodeGen::CodeGen(){
    
    
}

void CodeGen::Run(node* tree){
    traverseTree(tree, 0);
    
    cout << "Code Generator Complete.  No Errors" << endl;
    
}

void print2Target(string command, string token){
    string commandToPrint =  command + " " + token;
    fprintf(outFile, "%s", commandToPrint.c_str());
    
}

void CodeGen::traverseTree(node *tree, int depth) {
    token_t token1;
    
    
    if (tree == NULL) {
        return;
    } else {
        depth++;
    }
    
    
    
    

    
    
    if (DEVMODE) cout << "Checking child 1." << endl;
    if(tree->child1 != NULL){
        traverseTree(tree->child1, depth);
    }
    if (DEVMODE) cout << "Checking child 2." << endl;
    if(tree->child2 != NULL){
        traverseTree(tree->child2, depth);
    }
    if (DEVMODE) cout << "Checking child 3." << endl;
    if(tree->child3 != NULL){
        traverseTree(tree->child3, depth);
    }
    if (DEVMODE) cout << "Checking child 4." << endl;
    if(tree->child4 != NULL){
        traverseTree(tree->child4, depth);
    }
}



