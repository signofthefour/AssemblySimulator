#include <iostream>
#include "Label.h"

#pragma warning (disable : 4996)

using namespace std;

LabelTable::LabelTable()
{
	pFirst = NULL;
	pLast = NULL;
}

bool LabelTable::checkLabelExist(char* pCheckLabelContent)

{
	Label* pCurLabel = pFirst;
	while (pCurLabel != NULL)
	{
		if (strcmp((pCheckLabelContent), (pCurLabel->labelContent)) == 0) return true;
		pCurLabel = pCurLabel->pNext;
	}
	return false;
}

void LabelTable::addLabel(Label* newLabel)

{
	if (pFirst == NULL)
	{
		this->pFirst = newLabel;
		this->pLast = newLabel;
	}
	else
	{
		this->pLast->pNext = newLabel;
		this->pLast = newLabel;
	}
}

Label::Label(char* label, int commandAddr)
{
	this->addr = commandAddr;
	this->labelContent = label;
	this->pNext = NULL;
}

Label::Label()
{
	this->pNext = NULL;
}

bool isLabel(char* line, int commandAddr, LabelTable& tableLable)
{
	char* tempLabel = new char[255];
	int posInLine = 0;
	int lineLength = strlen(line);
	while (*(line + posInLine) == ' ' && posInLine < lineLength + 1)
	{
		posInLine++;
	}
	if (posInLine < lineLength + 1)
	{
		if (*(line + posInLine) < 'z' && *(line + posInLine) > 'A')
		{
			int posInTempLabel = 0;
			*(tempLabel + posInTempLabel) = *(line + posInLine);
			posInTempLabel++;

			// Get first satisfy chars
			while ( (*(line + posInLine++) < 'z' && *(line + posInLine) > 'A') ||
					(*(line + posInLine) < '9' && *(line + posInLine) > '0' ) )
			{
				*(tempLabel + posInTempLabel) = *(line + posInLine);
				posInTempLabel++;
			}
			// Check next chars
			while (*(line + posInLine) == ' ' && posInLine <= lineLength + 1) posInLine++;
			if (*(line + posInLine) == ':' && posInLine <= lineLength + 1) {
				posInLine++;
				while (*(line + posInLine) == ' ') posInLine++;
				if (*(line + posInLine) == '\0') 
				{ 
					*(tempLabel + posInTempLabel++) = '\0';
					char* label = new char[posInTempLabel++];
					strcpy(label, tempLabel);
					delete[] tempLabel;
					tempLabel = NULL;
					if (!tableLable.checkLabelExist(label))
					{
						Label* pNewLabel = new Label(label, commandAddr);
						tableLable.addLabel(pNewLabel);
					}
					else
					{
						return false;
					}
					return true; 
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}