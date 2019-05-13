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
string tempVariableValue;


using namespace std;

vector<string> tempVariableContainer;
vector<string> tempVariableValues;

CodeGen::CodeGen(){
    
    
}

string CodeGen::nextTempVariable(){
    string nextVariable;
    nextVariable = "T" + to_string(tempVariableCounter);
    return  nextVariable;
    
}

void CodeGen::Run(node* tree){
    traverseTree(tree, 0);
    print2Target("\nSTOP\n", "");
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
        return;
        
    } else if (tree->nodeLabel == "program"){
        if (DEVMODE) cout << "inside PROGRAM node" << endl;
        
        if (DEVMODE) cout << "Checking child 1." << endl;
        if(tree->child1 != NULL){
            traverseTree(tree->child1, depth);
        }
        
        if (DEVMODE) cout << "Checking child 2." << endl;
        if(tree->child2 != NULL){
            traverseTree(tree->child2, depth);
        }
        
        return;
    } else if (tree->nodeLabel == "block"){
        if (DEVMODE) cout << "inside BLOCK node" << endl;
        
        if (DEVMODE) cout << "Checking child 1." << endl;
        if(tree->child1 != NULL){
            traverseTree(tree->child1, depth);
        }
        if (DEVMODE) cout << "Checking child 2." << endl;
        traverseTree(tree->child2, depth);
        
        return;
        
    } else if (tree->nodeLabel == "vars"){
        if (DEVMODE) cout << "inside VARS node" << endl;
        print2Target("\nLOAD", tree->token1.tokenInstance);
        
        return;
        
    } else if (tree->nodeLabel == "stat"){
        if (DEVMODE) cout << "inside STAT node" << endl;
        
        traverseTree(tree->child1, depth);
        
        return;
        
    } else if (tree->nodeLabel == "stats"){
        if (DEVMODE) cout << "inside STATS node" << endl;
        
        if (DEVMODE) cout << "Checking child 1." << endl;
        traverseTree(tree->child1, depth);
  
        
        if (DEVMODE) cout << "Checking child 2 of stats." << endl;
        traverseTree(tree->child2, depth);
        
        return;
        
    } else if (tree->nodeLabel == "mStat"){
        if (DEVMODE) cout << "inside MSTAT node" << endl;

            traverseTree(tree->child1, depth);
            traverseTree(tree->child2, depth);
        

        return;
        
    } else if (tree->nodeLabel == "expr"){
        if (DEVMODE) cout << "inside EXPR node" << endl;
        if (tree->token1.tokenInstance == "+"){
            
        } else if (tree->token1.tokenInstance == "-"){
            
        } else {
            if (DEVMODE) cout << "Checking child 1." << endl;
          
            if(tree->child1 != NULL){
                traverseTree(tree->child1, depth);
            }
        }
    } else if (tree->nodeLabel == "A"){
        if (DEVMODE) cout << "inside A node" << endl;
        if (tree->token1.tokenInstance == "/"){
            tempVariable = nextTempVariable();
            tempVariableContainer.push_back(tempVariable);
            print2Target("LOAD", tempVariable);
            print2Target("\n", "");
            print2Target("DIV", tempVariable);
            print2Target("\n", "");
        } else {
            if (DEVMODE) cout << "Checking child 1." << endl;
            if(tree->child1 != NULL){
                traverseTree(tree->child1, depth);
            }
        }
        
    } else if (tree->nodeLabel == "N"){
        if (DEVMODE) cout << "inside N node" << endl;
        if (tree->token1.tokenInstance == "*" ){
            print2Target("LOAD", tempVariable);
            print2Target("\n", "");
            print2Target("MULT", tempVariable);
            print2Target("\n", "");
        } else {
            if(tree->child1 != NULL){
                traverseTree(tree->child1, depth);
            }
        }
        
        
    } else if (tree->nodeLabel == "M"){
        if (DEVMODE) cout << "inside M node" << endl;
        if (tree->token1.tokenInstance == "%"){
            print2Target("\nMULT", "-1");
        }
            traverseTree(tree->child1, depth);
        
        return;
    
    } else if (tree->nodeLabel == "R"){
        if (DEVMODE) cout << "inside R node" << endl;
        if (tree->token1.tokenID == identifierToken || tree->token1.tokenID == digitToken){
           print2Target("LOAD", tree->token1.tokenInstance);
        } else {
            if(tree->child1 != NULL){
                traverseTree(tree->child1, depth);
            }
        }
        
        return;

        
    } else if (tree->nodeLabel == "In"){
        if (DEVMODE) cout << "inside IN node" << endl;
        print2Target("\nREAD", "");
        print2Target("", tree->token1.tokenInstance);
        return;

        
    } else if (tree->nodeLabel == "Out"){
        if (DEVMODE) cout << "Checking child 1." << endl;
        
        traverseTree(tree->child1, depth);
        
        if (DEVMODE) cout << "inside OUT node" << endl;
        print2Target("\nSTORE", "");
        print2Target("\nWRITE", "");
        
   
        return;
        


    } else if (tree->nodeLabel == "IF"){
        if (DEVMODE) cout << "inside IF node" << endl;

        
    } else if (tree->nodeLabel == "loop"){
        if (DEVMODE) cout << "inside LOOP node" << endl;

        
    } else if (tree->nodeLabel == "assign"){
        if (DEVMODE) cout << "inside ASSIGN node" << endl;

        
    } else if (tree->nodeLabel == "RO"){
        if (DEVMODE) cout << "inside RO node" << endl;

        
    } else {
        depth++;
    }
    

    
    
//    if (DEVMODE) cout << "Checking child 1." << endl;
//    if(tree->child1 != NULL){
//        traverseTree(tree->child1, depth);
//    }
//    if (DEVMODE) cout << "Checking child 2." << endl;
//    if(tree->child2 != NULL){
//        traverseTree(tree->child2, depth);
//    }
//    if (DEVMODE) cout << "Checking child 3." << endl;
//    if(tree->child3 != NULL){
//        traverseTree(tree->child3, depth);
//    }
//    if (DEVMODE) cout << "Checking child 4." << endl;
//    if(tree->child4 != NULL){
//        traverseTree(tree->child4, depth);
//    }
}



