//
//  codeGen.cpp
//  P4
//
//  Created by Eric Goodwin on 5/5/19.
//  Copyright © 2019 umsl. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "statSem.h"
#include "node.h"
#include "token.h"
#include "codeGen.h"


const int DEVMODE = 1;

//reference https://www.geeksforgeeks.org/vector-in-cpp-stl/


using namespace std;

CodeGen::CodeGen(){
    
    
}

void CodeGen::Run(node* tree){
    traverseTree(tree, 0);
    
    cout << "Code Generator Complete.  No Errors" << endl;
    
}

void CodeGen::print2Target(string command, string token){
    string commandToPrint;
    if (token != "" ){
        commandToPrint =  command + " " + token;
    } else {
        commandToPrint = command;
    }
    fprintf(outFile, "%s", commandToPrint.c_str());

}


void CodeGen::traverseTree(node *tree, int depth) {
    token_t token1;
    
    
    if (tree == NULL) {
       print2Target("STOP", "");
        return;
    } else {
        depth++;
    }
    
    if (tree->nodeLabel == "program"){
        //do nothing, go to children
    }
    if (tree->nodeLabel == "block"){
        // do nothing, go to children
        
    }
    if (tree->nodeLabel == "vars"){
        // do nothing, variables written at end of file
    }
    if (tree->nodeLabel == "stat"){
        
    }
    if (tree->nodeLabel == "stats"){
        
    }
    if (tree->nodeLabel == "mStat"){
        
    }
    if (tree->nodeLabel == "expr"){
        
    }
    if (tree->nodeLabel == "A"){
        
    }
    if (tree->nodeLabel == "N"){
        
    }
    if (tree->nodeLabel == "M"){
        
    }
    if (tree->nodeLabel == "R"){
        
    }
    if (tree->nodeLabel == "IN"){
        
    }
    if (tree->nodeLabel == "OUT"){
        print2Target("WRITE", tree->token1.tokenInstance);
    }
    if (tree->nodeLabel == "IF"){
        
    }
    if (tree->nodeLabel == "loop"){
        
    }
    if (tree->nodeLabel == "assign"){
        
    }
    if (tree->nodeLabel == "RO"){
        
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



