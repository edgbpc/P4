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
int tempVariableCounter = 0;
string tempVariable;
//vector<string> globalContainer;

//reference https://www.geeksforgeeks.org/vector-in-cpp-stl/

vector<string> tempVariableContainer;
vector<string> tempVariableValues;

using namespace std;

CodeGen::CodeGen(){
    
    
}

string CodeGen::nextTempVariable(){
    string nextVariable;
    nextVariable = "T" + to_string(tempVariableCounter);
    return  nextVariable;
    
}

void CodeGen::Run(node* tree){
    traverseTree(tree, 0);
    print2Target("STOP\n", "");
    for (int i = 0; i < globalContainer.size(); i++){
        print2Target(globalContainer[i], "");
        print2Target("", globalValues[i]);
        print2Target("\n", "");
    }
    for (int i = 0; i < tempVariableContainer.size(); i++){
        print2Target(tempVariableContainer[i], "");
        print2Target("", tempVariableValues[i]);
        print2Target("\n", "");
    }
    
    print2Target("\n", "");
    
    cout << "Code Generator Complete.  No Errors" << endl;
    
}

void CodeGen::print2Target(string command, string token){
    string commandToPrint;
    if (token != "" ){
        commandToPrint =  command + " " + token;
    } else if (token == ""){
        commandToPrint = command;
    } else if (command != "") {
        commandToPrint = "" + token;
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
        if (tree->token1.tokenInstance == "+"){
            
        } else if (tree->token1.tokenInstance == "-"){
            
        } else {
            //do nothing, calls child
        }
        
        

        
    }
    if (tree->nodeLabel == "A"){
        if (DEVMODE) cout << "inside A node" << endl;

        
    }
    if (tree->nodeLabel == "N"){
        if (DEVMODE) cout << "inside N node" << endl;
        if (tree->token1.tokenInstance == "*" ){
            tempVariable = nextTempVariable();
            tempVariableContainer.push_back(tempVariable);
            print2Target("STORE", tempVariable);
            print2Target("\n", "");
            print2Target("MULTI", tempVariable);
            print2Target("\n", "");
        }
        
        
    }
    if (tree->nodeLabel == "M"){
        if (DEVMODE) cout << "inside M node" << endl;

    }
    if (tree->nodeLabel == "R"){
        if (DEVMODE) cout << "inside R node" << endl;
        if (tree->token1.tokenID == identifierToken || tree->token1.tokenID == digitToken){
            print2Target("", tree->token1.tokenInstance);
            print2Target("\n", "");
        }

        
    }
    if (tree->nodeLabel == "In"){
        if (DEVMODE) cout << "inside IN node" << endl;
        print2Target("READ", "");
        print2Target("", tree->token1.tokenInstance);
        print2Target("\n", "");

        
    }
    if (tree->nodeLabel == "Out"){
        if (DEVMODE) cout << "inside OUT node" << endl;
        print2Target("WRITE", "");
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



