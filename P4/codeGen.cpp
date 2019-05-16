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
int tempVariableCounter = 1;
string tempVariable = "";
int nextLabelCounter = 1;
string label = "";
int printHelper = 0;

using namespace std;

CodeGen::CodeGen(){
    
    
}



string CodeGen::nextTempVariable(){
    string nextVariable;
    nextVariable = "T" + to_string(tempVariableCounter);
    cout << "Next Variable is " << nextVariable << endl;
    tempVariableCounter++;
    return  nextVariable;
    
}

string CodeGen::nextLabel(){
    string nextLabel;
    nextLabel = "L" + to_string(nextLabelCounter);
    cout << "Next Label is " << nextLabel << endl;
    nextLabelCounter++;
	
    return nextLabel;
}

string previousTempVariable(){
	string previousTempVariable;
	previousTempVariable = "T" + to_string(tempVariableCounter - 2);
	cout << "previous variable was " << previousTempVariable << endl;
	return previousTempVariable;
}


void CodeGen::Run(node* tree){
    
    traverseTree(tree, 0);
    print2Target("\nSTOP\n", "");
    for (int i = 0; i < globalContainer.size(); i++){
        print2Target(globalContainer[i], "");
        print2Target("", globalValues[i]);
        print2Target("\n", "");
    }
    for (int i = 0; i < tempVariableCounter; i++){
    	print2Target("T", "");
	print2Target(to_string(i), "");
	print2Target("", "0\n");
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
        traverseTree(tree->child1, depth);

        
        if (DEVMODE) cout << "Checking child 2." << endl;
        traverseTree(tree->child2, depth);

        
        return;
    } else if (tree->nodeLabel == "block"){
        if (DEVMODE) cout << "inside BLOCK node" << endl;
        
        if (DEVMODE) cout << "Checking child 1." << endl;
        traverseTree(tree->child1, depth);

        if (DEVMODE) cout << "Checking child 2." << endl;
        traverseTree(tree->child2, depth);
        
        return;
        
    } else if (tree->nodeLabel == "vars"){
        if (DEVMODE) cout << "inside VARS node" << endl;
        traverseTree(tree->child1, depth);
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
	if (tree->child2 != NULL){
	    traverseTree(tree->child2, depth);
            tempVariable = nextTempVariable();    
	    print2Target("\nSTORE", tempVariable);	
            traverseTree(tree->child1, depth);
            if (tree->token1.tokenInstance == "+"){
		    print2Target("\nADD", tempVariable);
		    return;
	    } else if (tree->token1.tokenInstance == "-"){
		    print2Target("\nSUB", tempVariable);
		    return;
	    } else {
		    //nothing
		    return;
	    }
	} else {
		traverseTree(tree->child1, depth);
		return;
	}
	 

    } else if (tree->nodeLabel == "A"){
        if (DEVMODE) cout << "inside A node" << endl;
	if (tree->token1.tokenInstance == ""){
		traverseTree(tree->child1, depth);
		return;
	} else if (tree->token1.tokenInstance == "/"){
            traverseTree(tree->child2, depth);
	    tempVariable = nextTempVariable();
	    print2Target("\nSTORE", tempVariable);
	    traverseTree(tree->child1, depth);
	    print2Target("\nDIV", previousTempVariable());
	    return;
        }
        
    } else if (tree->nodeLabel == "N"){
        if (DEVMODE) cout << "inside N node" << endl;
	if (tree->token1.tokenInstance == ""){
		traverseTree(tree->child1, depth);
		return;
	} else if (tree->token1.tokenInstance == "*" ){
	    traverseTree(tree->child2, depth);
	    tempVariable = nextTempVariable();
	    print2Target("\nSTORE", tempVariable);
	    traverseTree(tree->child1, depth);
	    print2Target("\nMULT", tempVariable);
            return;
       	}
        
    	
        
    } else if (tree->nodeLabel == "M"){

        if (DEVMODE) cout << "inside M node" << endl;
        if (tree->token1.tokenInstance == "%"){
            traverseTree(tree->child1, depth);

            print2Target("\nMULT", "-1");
            
            return;
            
        }             
	 
	traverseTree(tree->child1, depth);
        return;
	
    
    } else if (tree->nodeLabel == "R"){
        if (DEVMODE) cout << "inside R node" << endl;
        if (tree->token1.tokenID == digitToken || tree->token1.tokenID == identifierToken) {
            print2Target("\nLOAD", tree->token1.tokenInstance);
	    return;
	
        } else {
            traverseTree(tree->child1, depth);
            return;
          }
    
    
    } else if (tree->nodeLabel == "In"){
        if (DEVMODE) cout << "inside IN node" << endl;
        print2Target("\nREAD", tree->token1.tokenInstance);
	print2Target("\nLOAD", tree->token1.tokenInstance);
	return;

        
    } else if (tree->nodeLabel == "Out"){
        if (DEVMODE) cout << "inside OUT node" << endl;
	traverseTree(tree->child1, depth);      
        tempVariable = nextTempVariable();
        print2Target("\nSTORE", tempVariable);
        print2Target("\nWRITE", tempVariable);

   
        return;
        


    } else if (tree->nodeLabel == "If"){
        if (DEVMODE) cout << "inside IF node" << endl;
	traverseTree(tree->child3, depth);
	tempVariable = nextTempVariable();
	print2Target("\nSTORE", tempVariable);
	traverseTree(tree->child1, depth);
	print2Target("\nSUB", tempVariable);
	label = "Out";
	traverseTree(tree->child2, depth);
	traverseTree(tree->child4, depth);
	print2Target("\n", "");
	print2Target(label, "");
	print2Target(":", "NOOP");
	return;
        
    } else if (tree->nodeLabel == "loop"){

       if (DEVMODE) cout << "inside LOOP node" << endl;
	
        string label1 = nextLabel();
	string label2 = nextLabel();
        print2Target("\n", "");
	print2Target(label1, "");
	print2Target(":", "NOOP");
	traverseTree(tree->child1, depth);
	tempVariable = nextTempVariable();
	print2Target("\nSTORE", tempVariable);
	
	traverseTree(tree->child3, depth);
	print2Target("\nSUB", tempVariable);

	if (tree->child2->token1.tokenInstance == ">"){
		if(tree->child2->token2.tokenInstance == ""){
			print2Target("\nBRZPOS", label2); //BRZNEG
		} else {
			//nothing
		}
	} else if (tree->child2->token1.tokenInstance == "<"){
		if (tree->child2->token2.tokenInstance == ""){
			print2Target("\nBRZNEG", label2); //BRPOS
		} else if (tree->child2->token2.tokenInstance == ">"){
			print2Target("\nBRZERO", label2);  //BRZERO
		} else {
			//nothing
		}
	} else if (tree->child2->token1.tokenInstance == "="){
		if (tree->child2->token2.tokenInstance == ">"){
			print2Target("\nBRPOS", label2); //BRNEG
		} else if (tree->child2->token2.tokenInstance == "<"){
			print2Target("\nBRNEG", label2); //BRPOS
		}
	}
   
	

	traverseTree(tree->child4, depth);
	print2Target("\nBR", label1);
	print2Target("\n", "");
	print2Target(label2, "");
	print2Target(":", "NOOP");
	return;
        
    } else if (tree->nodeLabel == "assign"){
        if (DEVMODE) cout << "inside ASSIGN node" << endl;
	traverseTree(tree->child1, depth);
	print2Target("\nSTORE", tree->token1.tokenInstance);

        return;
    } else if (tree->nodeLabel == "RO"){
        if (DEVMODE) cout << "inside RO node" << endl;

	if (tree->token1.tokenInstance == ">"){
		if (tree->token2.tokenInstance == ""){
			print2Target("\nBRZNEG", label);
			return;
		} else {
	   		//nothing
		}		
	} else if (tree->token1.tokenInstance == "<"){
		if (tree->token2.tokenInstance == ""){
			print2Target("\nBRZPOS", label);
			return;
		
		} else if (tree->token2.tokenInstance == ">"){
			print2Target("\nBRZERO", label);
			return;
		} else {
			//nothing
		}
	} else if (tree->token1.tokenInstance == "="){
	       if (tree->token2.tokenInstance == ">"){
		       print2Target("\nBRNEG", label);
		       return;
	       } else if (tree->token2.tokenInstance == "<"){
		       print2Target("\nBRPOS", label); 
		       return;
	       } else if (tree->token2.tokenInstance == ""){
		       print2Target("\nBRNEG", label);
		       print2Target("\nBRPOS", label);
		       return;
		} else {
			//nothing
		}
	}

        return;
        
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



