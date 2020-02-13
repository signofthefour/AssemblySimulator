#include "Register.h"

const char* registerListCheck[] = { "zero", "at", "v0", "v1", "a0", "a1",
									"a2", "a3", "t0", "t1", "t2", "t3", "t4",
									"t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4",
									"s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra", "pc" };

int compareRegister(char * registerName)
{
	{
		for (int i = 0; i < (sizeof(registerListCheck)/4); i++)
		{
			if (strcmp(registerName, registerListCheck[i]) == 0)
			{
				return i;
			}
		}
		return -1;
	}
}

int getAndCheckRegisterName(char * line, int & posInLine)
{
	while (*(line + posInLine) == ' ') posInLine++;
	if (*(line + posInLine) == '$')
	{
		char* tmpRegisterName = new char[5];
		int posInTmpRegisterName = 0;
		posInLine++;
		while ((*(line + posInLine) >= 'a' && *(line + posInLine) <= 'z') || (*(line + posInLine) < '9' && *(line + posInLine) > '0'))
		{
			if (posInTmpRegisterName > 6) throw "Completed with errors. ";
			*(tmpRegisterName + posInTmpRegisterName) = *(line + posInLine);
			posInLine++;
			posInTmpRegisterName++;
		}
		*(tmpRegisterName + posInTmpRegisterName) = '\0';
		while (*(line + posInLine) == ' ') posInLine++;
		char* registerName = new char[posInTmpRegisterName];
		strcpy(registerName, tmpRegisterName);
		delete[] tmpRegisterName;
		tmpRegisterName = NULL;
		int registerOrder = compareRegister(registerName);
		if (registerOrder == -1)
		{
			throw "Completed with errors. Wrong variable";
		}
		else
		{
			return registerOrder;
		}
	}
	throw "Completed with errors. Wrong variable";
}

int getAndCheckImmediate(char* line, int& posInLine)
{
	int value = 0;
	bool isNegative = false;
	while (*(line + posInLine) == ' ') posInLine++;
	int countNumber = -1;
	char arr[10];
	if (line[posInLine] == '-') {
		isNegative = true;
		posInLine++;
	}
	while (*(line + posInLine) >= '0' && *(line + posInLine) <= '9')
	{
		countNumber++;
		arr[countNumber] = *(line + posInLine);
		posInLine++;
	}
	for (int i = countNumber; i >= 0; i--)
	{
		value += (int)(arr[i] - 48) * (int)(pow(10, countNumber - i));
	}
	if (isNegative == true) value = -value;
	return value;
} // Register.cpp

void RegisterList::printAllRegister()
{
	printf(" Register Name  |  Register Number  |       Value\n");
	printf("----------------|-------------------|------------------\n");
	printf("$zero           | 0                 | %d\n", zero);
	printf("$at             | 1                 | %d\n", at);
	printf("$v0             | 2                 | %d\n", v0);
	printf("$v1             | 3                 | %d\n", v1);
	printf("$a0             | 4                 | %d\n", a0);
	printf("$a1             | 5                 | %d\n", a1);
	printf("$a2             | 6                 | %d\n", a2);
	printf("$a3             | 7                 | %d\n", a3);
	printf("$t0             | 8                 | %d\n", t0);
	printf("$t1             | 9                 | %d\n", t1);
	printf("$t2             | 10                | %d\n", t2);
	printf("$t3             | 11                | %d\n", t3);
	printf("$t4             | 12                | %d\n", t4);
	printf("$t5             | 13                | %d\n", t5);
	printf("$t6             | 14                | %d\n", t6);
	printf("$t7             | 15                | %d\n", t7);
	printf("$s0             | 16                | %d\n", s0);
	printf("$s1             | 17                | %d\n", s1);
	printf("$s2             | 18                | %d\n", s2);
	printf("$s3             | 19                | %d\n", s3);
	printf("$s4             | 20                | %d\n", s4);
	printf("$s5             | 21                | %d\n", s5);
	printf("$s6             | 22                | %d\n", s6);
	printf("$s7             | 23                | %d\n", s7);
	printf("$t8             | 24                | %d\n", t8);
	printf("$t9             | 25                | %d\n", t9);
	printf("$k0             | 26                | %d\n", k0);
	printf("$k1             | 27                | %d\n", k1);
	printf("$gp             | 28                | %d\n", gp);
	printf("$sp             | 29                | %d\n", sp);
	printf("$fp             | 30                | %d\n", fp);
	printf("$ra             | 31                | %d\n", ra);
	printf("pc              |                   | %d\n", pc);
}
