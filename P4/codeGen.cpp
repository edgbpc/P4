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
        if (DEVMODE) cout << "at end of tree" << endl;

       print2Target("STOP", "");
        return;
    } else {
        depth++;
    }
    
    if (tree->nodeLabel == "program"){
         if (DEVMODE) cout << "inside PROGRAM node" << endl;
    }
    if (tree->nodeLabel == "block"){
        if (DEVMODE) cout << "inside BLOCK node" << endl;

    }
    if (tree->nodeLabel == "vars"){
        if (DEVMODE) cout << "inside VARS node" << endl;
    }
    if (tree->nodeLabel == "stat"){
        if (DEVMODE) cout << "inside STAT node" << endl;

        
    }
    if (tree->nodeLabel == "stats"){
        if (DEVMODE) cout << "inside STATS node" << endl;

        
    }
    if (tree->nodeLabel == "mStat"){
        if (DEVMODE) cout << "inside MSTAT node" << endl;

        
    }
    if (tree->nodeLabel == "expr"){
        if (DEVMODE) cout << "inside EXPR node" << endl;

        
    }
    if (tree->nodeLabel == "A"){
        if (DEVMODE) cout << "inside A node" << endl;

        
    }
    if (tree->nodeLabel == "N"){
        if (DEVMODE) cout << "inside N node" << endl;

        
    }
    if (tree->nodeLabel == "M"){
        if (DEVMODE) cout << "inside M node" << endl;

    }
    if (tree->nodeLabel == "R"){
        if (DEVMODE) cout << "inside R node" << endl;

        
    }
    if (tree->nodeLabel == "IN"){
        if (DEVMODE) cout << "inside IN node" << endl;

        
    }
    if (tree->nodeLabel == "OUT"){
        if (DEVMODE) cout << "inside OUT node" << endl;
        print2Target("WRITE", tree->token1.tokenInstance);
    }
    if (tree->nodeLabel == "IF"){
        if (DEVMODE) cout << "inside IF node" << endl;

        
    }
    if (tree->nodeLabel == "loop"){
        if (DEVMODE) cout << "inside LOOP node" << endl;

        
    }
    if (tree->nodeLabel == "assign"){
        if (DEVMODE) cout << "inside ASSIGN node" << endl;

        
    }
    if (tree->nodeLabel == "RO"){
        if (DEVMODE) cout << "inside RO node" << endl;

        
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



