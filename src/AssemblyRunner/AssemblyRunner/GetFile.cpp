#pragma warning (disable: 4996)
#include "GetFile.h"

int processLine(LabelTable& tableLabel, RegisterList*& registerList)
{
	char* fileName = getNameOfFile();
	fstream file(fileName);
	file.seekg(0, file.end);
	int fileSize = file.tellg();
	file.seekg(0, file.beg);
	int commandAddr = 0;
	if (fileSize > 0)
	{
		while (!file.eof())
		{
			char* line = getLine(file);
			int curPos = determineTypeOfLine(line, commandAddr, tableLabel, registerList);
		}
	}
	else
	{
		throw "Please check the name of your file!";
	}
	file.close();
	return commandAddr;
}

char* getNameOfFile()
{
	char* tempName = new char[255];
	cout << "Name of input file: ";
	char ch;
	cin >> ch;
	int nameLength = 0;
	while (ch != '\n')
	{
		*(tempName + nameLength) = ch;
		nameLength++;
		cin.get(ch);
	}
	*(tempName + nameLength) = '\0';
	char* fileName = new char[nameLength];
	strcpy(fileName, tempName);
	delete[] tempName;
	return fileName;
}

char* getLine(fstream &file)
{
	char* tempLine = new char[256];
	char ch;
	file >> ch;
	int pos = 0;
	while (ch != '\n' && !file.eof())
	{
		*(tempLine + pos) = ch;
		pos++;    
		ch = file.get();
	}
	*(tempLine + pos) = '\0';
	char* line = new char[pos + 1]; 
	strcpy(line, tempLine);
	delete[] tempLine;
	tempLine = NULL;
	return line;
}

int determineTypeOfLine(char* &line, int& commandArr, LabelTable& tableLabel, RegisterList*& registerList)
{
	if (!isComment(line))
	{
		if (!isLabel(line, commandArr, tableLabel))
		{
			
			if (isCommand(line, commandArr, registerList, tableLabel))
			{
				return 0;
			}
			throw "Completed with errors. Not in rule of syntax";
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

void declareVariables(char *& line)
{
	cout << "so far so good" << endl;
	system("pause");
}


//=======================================================================================================