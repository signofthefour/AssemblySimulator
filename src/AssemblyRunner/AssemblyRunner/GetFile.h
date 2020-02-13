#pragma once
#ifndef _GET_FILE_AND_CHECK_
#define _GET_FILE_AND_CHECK_
#include <fstream>
#include "Label.h"
#include "Comment.h"
#include "Command.h"
#include <iostream>

using namespace std;

int processLine(LabelTable& tableLabel, RegisterList*& registerList);
char* getNameOfFile();
char* getLine(fstream &file);
int determineTypeOfLine(char*& line, int& commandAddr, LabelTable& tableLabel, RegisterList*& registerList);
void declareVariables(char*& line);

#endif // !_GET_FILE_AND_CHECK_
