#include <iostream>
#include <fstream>
#include "GetFile.h"
#include "Label.h"
#include "Command.h"
#include "Comment.h"
#include "Execute.h"

RegisterList* registerList =  new RegisterList;
LabelTable labelTable;

using namespace std;

int main()
{	
	cout << "===========================================================" << endl;
	cout << "Original state of register list" << endl;
	cout << "===========================================================" << endl;
	registerList->printAllRegister();
	cout << "===========================================================" << endl;
	cout << "Press Enter to compile the code." << endl;
	cout << "===========================================================" << endl;
	system("pause");
	system("cls");

	int numOfElements = -1;
	try
	{
		numOfElements = processLine(labelTable, registerList);
	}
	catch (const char* exMsg)
	{
		cout << exMsg << endl;
		system("pause");
	}
	system("cls");

	cout << "===========================================================" << endl;
	cout << "Done! Press Enter to execute the code." << endl;
	cout << "===========================================================" << endl;
	system("pause");
	system("cls");
	try 
	{
		if (numOfElements < 1) throw "Completed with errors. No command!";
		CommandLine** commandTable = new CommandLine*[numOfElements + 1];
		createCommandTable(commandTable);
		execute(commandTable, labelTable, registerList);
	}
	catch (const char* exMsg)
	{
		cout << exMsg << endl;
	}
	system("pause");
	return 0;
}