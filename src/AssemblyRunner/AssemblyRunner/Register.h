#pragma once
#ifndef _COMMAND_AND_LABEL_CLASS_
#define _COMMAND_AND_LABEL_CLASS_
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#pragma warning (disable : 4996)

struct RegisterList
{
	short zero = 0;
	short at = 0;
	short v0 = 0;
	short v1 = 0;
	short a0 = 0;
	short a1 = 0;
	short a2 = 0;
	short a3 = 0;
	short t0 = 0;
	short t1 = 0;
	short t2 = 0;
	short t3 = 0;
	short t4 = 0;
	short t5 = 0;
	short t6 = 0;
	short t7 = 0;
	short s0 = 0;
	short s1 = 0;
	short s2 = 0;
	short s3 = 0;
	short s4 = 0;
	short s5 = 0;
	short s6 = 0;
	short s7 = 0;
	short t8 = 0;
	short t9 = 0;
	short k0 = 0;
	short k1 = 0;
	short gp = 0;
	short sp = 0;
	short fp = 0;
	short ra = 0;
	int pc = 0;

	void printAllRegister();
};

int compareRegister(char * registerName);
int getAndCheckRegisterName(char* line, int&posInLine);
int getAndCheckImmediate(char* line, int& posInLine);

#endif // !_COMMAND_CLASS_
