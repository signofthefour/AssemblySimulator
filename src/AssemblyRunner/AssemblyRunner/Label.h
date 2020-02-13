#pragma once
#ifndef _LABEL_ASSEMBLY_
#define _LABEL_ASSEMBLY_
/* Each label is managed by one struct. */
struct Label
{
	int addr;
	char* labelContent;
	Label* pNext;
	Label(char* label, int linePos);
	Label();
};

/* Every labels are managed by a struct. */
struct LabelTable
{
	Label* pFirst;
	Label* pLast;
	LabelTable();
	bool checkLabelExist(char* pLabelContent);
	void addLabel(Label* newLabel);
};

bool isLabel(char* line, int linePos, LabelTable& tableLabel);

#endif // !_LABEL_ASSEMBLY_
