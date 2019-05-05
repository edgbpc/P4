//
//  scanner.hpp
//  P1
//
//  Created by Eric Goodwin on 3/28/19.
//  Copyright © 2019 umsl. All rights reserved.
//

#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include "token.h"

void checkCharacter(partialToken_t tokenFragment);
void scanner(partialToken_t tokenFragment);
void filter1(char workingCharacter);
bool filter2(token_t token);
void determineTokenType(int stateIndex);
void printToken(token_t token);
void clearTokenCurrent();
void processFinalTokenState();
void filter2();
void executeScanner(char workingCharacter);
token_t getFinalToken();
void processCharacter(int state);

extern bool isTokenComplete;


const string reservedWords[11] = {"iter", "void", "var", "return", "scan", "print", "program", "cond", "then", "let", "int"};

#endif /* scanner_h */
