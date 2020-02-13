#include "Command.h"
#pragma warning (disable: 4996)
using namespace std;

//instruction
const char* jTypeCheckList[] = { "j", "jal" };
const char* rTypeCheckList[] = { "add", "jr", "and", "nor", "or", "slt", "sltu", "sll", "srl", "sub", "subu", "div", "divu", "mult", "multu" };
const char* iTypeCheckList[] = { "addi", "addiu", "andi", "beq", "bne", "lbu", "lhu", "ll", "lui", "lw", "ori", "slti", "sltiu", "sb", "sw" };
const char* pseudoTypeCheckList[] = {"li"};

CommandLinkedList commandLinkedList;

CommandLinkedList::CommandLinkedList()
{
	this->pFirst = NULL;
	this->pLast = NULL;
}

void CommandLinkedList::addCommand(CommandNode * newNode)
{
	if (this->pFirst == NULL)
	{
		this->pFirst = newNode;
		this->pLast = newNode;
	}
	else
	{
		this->pLast->pNext = newNode;
		this->pLast = newNode;
	}
}

bool isCommand(char* line, int& commandAddr, RegisterList*& registerList, LabelTable& labelTabel)
{
	int posInLine = 0;
	char* opcode = new char[6];

	while (*(line + posInLine) == ' ')
	{
		posInLine++;
	}

	int posInOpcode = 0;

	while (*(line + posInLine) != ' ')
	{
		if (posInOpcode == 5) return false;
		if (*(line + posInLine) <= 'z' && *(line + posInLine) >= 'a')
		{
			*(opcode + posInOpcode) = *(line + posInLine);
			posInLine++;
			posInOpcode++;
		}
		else return false;
	}
	*(opcode + posInOpcode) = '\0';
	posInOpcode++;
	//Shorten opcode array
	char* newOpcode = new char[posInOpcode];
	strcpy(newOpcode, opcode);
	delete[] opcode;
	opcode = NULL;
	int opcodeID = 0;
	for (int i = 0; i < (sizeof(jTypeCheckList) / 4); i++) /*Check if the instruciton is jType*/
	{
		if (strcmp(newOpcode, *(jTypeCheckList + i)) == 0)
		{
			CommandNode* newNode = new CommandNode(checkCommand(opcodeID, line, posInLine, registerList, labelTabel, commandAddr));
			if (newNode != NULL)
			{
				commandLinkedList.addCommand(newNode);
				commandAddr++; 
				return true;
			}
			throw "Commpleted with errors.";
		}
		opcodeID++;
	}

	for (int i = 0; i < (sizeof(rTypeCheckList) / 4); i++) /*Check if the instruciton is rType*/
	{
		if (strcmp(newOpcode, *(rTypeCheckList + i)) == 0)
		{
			CommandNode* newNode = new CommandNode(checkCommand(opcodeID, line, posInLine, registerList, labelTabel, commandAddr));
			if (newNode != NULL)
			{
				commandLinkedList.addCommand(newNode);
				commandAddr++;
				return true;
			}
			throw "Commpleted with errors.";
		}
		opcodeID++;
	}

	for (int i = 0; i < (sizeof(iTypeCheckList) / 4); i++) /*Check if the instruciton is iType*/
	{
		if (strcmp(newOpcode, iTypeCheckList[i]) == 0)
		{
			CommandNode* newNode = new CommandNode(checkCommand(opcodeID, line, posInLine, registerList, labelTabel, commandAddr));
			if (newNode != NULL)
			{
				commandLinkedList.addCommand(newNode);
				commandAddr++;
				return true;
			}
			throw "Commpleted with errors.";
		}
		opcodeID++;
	}

	for (int i = 0; i < (sizeof(pseudoTypeCheckList) / 4); i++) /*Check if the instruciton is pseudoType*/
	{
		if (strcmp(newOpcode, pseudoTypeCheckList[i]) == 0)
		{
			CommandNode* newNode = new CommandNode(checkCommand(opcodeID, line, posInLine, registerList, labelTabel, commandAddr));
			if (newNode != NULL)
			{
				commandLinkedList.addCommand(newNode);
				commandAddr++;
				return true;
			}
			throw "Commpleted with errors.";
		}
		opcodeID++;
	}
	return false;
}

CommandLine* checkCommand(int opcodeID, char* line, int posInLine, RegisterList*& registerList, LabelTable& tableLabel, int commandAddr) /*Check if the command is right write*/
{
	switch (opcodeID)
	{
	case ADD: /*add instruction*/
		{
			AddInstruction* addInstruction = new AddInstruction;
			addInstruction->opcode = opcodeID;
			if (addInstruction->check(line, posInLine, registerList)) return (CommandLine*)addInstruction;
			break;
		}
	case SUB:
	{
		SubInstruction* subInstruction = new SubInstruction;
		subInstruction->opcode = opcodeID;
		if (subInstruction->check(line, posInLine, registerList)) return (CommandLine*)subInstruction;
		break;
	}
	case J: /*j instruction*/
		{
			JumpInstruction* jumpInstruction = new JumpInstruction;
			jumpInstruction->opcode = opcodeID;
			if (jumpInstruction->check(line, posInLine, tableLabel)) return (CommandLine*)jumpInstruction;
			break;
		}
	case BEQ: /*beq instruction*/
		{
			BeqInstruction* beqInstruction = new BeqInstruction;
			beqInstruction->opcode = opcodeID;
			if (beqInstruction->check(line, posInLine, registerList)) return (CommandLine*)beqInstruction;
			break;
		}
	case BNE:
	{
		BneInstruction* bneInstruction = new BneInstruction;
		bneInstruction->opcode = opcodeID;
		if (bneInstruction->check(line, posInLine, registerList)) return (CommandLine*)bneInstruction;
		break;
	}
	case ADDI:
	{
		AddiInstruction* addiInstruction = new AddiInstruction;
		addiInstruction->opcode = opcodeID;
		if (addiInstruction->check(line, posInLine, registerList)) return (CommandLine*)addiInstruction;
		break;
	}
	case LI:
	{
		LiInstruction* liInstruction = new LiInstruction;
		liInstruction->opcode = opcodeID;
		if (liInstruction->check(line, posInLine, registerList)) return (CommandLine*)liInstruction;
		break;
	}
	case JAL:
	{
		JalInstruction* jalInstruction = new JalInstruction;
		jalInstruction->opcode = opcodeID;
		if (jalInstruction->check(line, posInLine, tableLabel)) return (CommandLine*)jalInstruction;
		break;
	}
	case JR:
	{
		JrInstruction* jrInstruction = new JrInstruction;
		jrInstruction->opcode = opcodeID;
		if (jrInstruction->check(line, posInLine, registerList)) return (CommandLine*)jrInstruction;
		break;
	}
	case AND:
	{
		AndInstruction* andInstruction = new AndInstruction;
		andInstruction->opcode = opcodeID;
		if (andInstruction->check(line, posInLine, registerList)) return (CommandLine*)andInstruction;
		break;
	}
	case NOR:
	{
		NorInstruction* norInstruction = new NorInstruction;
		norInstruction->opcode = opcodeID;
		if (norInstruction->check(line, posInLine, registerList)) return (CommandLine*)norInstruction;
		break;
	}
	case OR:
	{
		OrInstruction* orInstruction = new OrInstruction;
		orInstruction->opcode = opcodeID;
		if (orInstruction->check(line, posInLine, registerList)) return (CommandLine*)orInstruction;
		break;
	}
	case SLT:
	{
		SltInstruction* sltInstruction = new SltInstruction;
		sltInstruction->opcode = opcodeID;
		if (sltInstruction->check(line, posInLine, registerList)) return (CommandLine*)sltInstruction;
		break;
	}
	case SLTU:
	{
		SltuInstruction* sltuInstruction = new SltuInstruction;
		sltuInstruction->opcode = opcodeID;
		if (sltuInstruction->check(line, posInLine, registerList)) return (CommandLine*)sltuInstruction;
		break;
	}
	case SLL:
	{
		SllInstruction* sllInstruction = new SllInstruction;
		sllInstruction->opcode = opcodeID;
		if (sllInstruction->check(line, posInLine, registerList)) return (CommandLine*)sllInstruction;
		break;
	}
	case SRL:
	{
		SrlInstruction* srlInstruction = new SrlInstruction;
		srlInstruction->opcode = opcodeID;
		if (srlInstruction->check(line, posInLine, registerList)) return (CommandLine*)srlInstruction;
		break;
	}
	case SUBU:
	{
		SubuInstruction* subuInstruction = new SubuInstruction;
		subuInstruction->opcode = opcodeID;
		if (subuInstruction->check(line, posInLine, registerList)) return (CommandLine*)subuInstruction;
		break;
	}
	case DIV:
	{
		DivInstruction* divInstruction = new DivInstruction;
		divInstruction->opcode = opcodeID;
		if (divInstruction->check(line, posInLine, registerList)) return (CommandLine*)divInstruction;
		break;
	}
	case DIVU:
	{
		DivuInstruction* divuInstruction = new DivuInstruction;
		divuInstruction->opcode = opcodeID;
		if (divuInstruction->check(line, posInLine, registerList)) return (CommandLine*)divuInstruction;
		break;
	}
	case MULT:
	{
		MultInstruction* multInstruction = new MultInstruction;
		multInstruction->opcode = opcodeID;
		if (multInstruction->check(line, posInLine, registerList)) return (CommandLine*)multInstruction;
		break;
	}
	case MULTU:
	{
		MultuInstruction* multuInstruction = new MultuInstruction;
		multuInstruction->opcode = opcodeID;
		if (multuInstruction->check(line, posInLine, registerList)) return (CommandLine*)multuInstruction;
		break;
	}
	default: /*everything else return NULL mean there is a NULL command will be created*/
		throw "This is not a command.";
		return NULL;
		break;
	}
	return NULL;
}

void createCommandTable(CommandLine** &commandTable)
{	
	
	/*CommandLinkedList is already*/
	CommandNode* curCommandNode = commandLinkedList.pFirst; /*curCommand is the pFirst of commandList*/
	int posInCommandTable = 0;
	while (curCommandNode != NULL)
	{
		commandTable[posInCommandTable] = curCommandNode->pCommandLine; /*initialize the posInCommandTableTH element by curCommandNode*/
		posInCommandTable++;
		commandLinkedList.pFirst = curCommandNode->pNext; /*initialize the pFirst by the next commandNode*/
		delete curCommandNode;
		curCommandNode = NULL;
		curCommandNode = commandLinkedList.pFirst; /*now, the curCommandNode is the next command of the origin in this loop*/
	}
	commandTable[posInCommandTable] = NULL;
}

bool AddInstruction::check(char * line, int posInLine, RegisterList*& registerList)
{
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rd = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rt = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void AddInstruction::execute()
{
	*rd = *rs + *rt;
}

bool JumpInstruction::check(char * line, int posInLine, LabelTable & tableLabel)
{
	char* temp = new char[255];
	int linePos = 0;
	while (line[linePos] == ' ') linePos++;
	linePos++;
	while (line[linePos] == ' ') linePos++;
	int begPos = linePos;
	while (line[linePos] != '\0' && line[linePos] != ' ') {
		temp[linePos - begPos] = line[linePos];
		linePos++;
	}
	temp[linePos - begPos] = '\0';
	char* destinationLabel = new char[linePos - begPos + 1];
	strcpy(destinationLabel, temp);
	while (line[linePos] == ' ') linePos++;
	if (line[linePos] != '\0') return false;
	delete[] temp;
	this->destination = destinationLabel;
	return true;
}

void JumpInstruction::execute(int &commandAddr, LabelTable labeltable)
{
	bool isLabelExisting = labeltable.checkLabelExist(this->destination);
	if (isLabelExisting) {
		Label* pCurLabel = labeltable.pFirst;
		while (pCurLabel != NULL)
		{
			if (strcmp(this->destination, pCurLabel->labelContent) == 0) break;
			pCurLabel = pCurLabel->pNext;
		}
		commandAddr = pCurLabel->addr;
	}
	else throw "Complete with errors. Wrong label";
}

bool BeqInstruction::check(char* line, int posInLine, RegisterList*& registerList) {
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = (short*)&(registerList[registerOrder]);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors. Wrong syntax";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rt = (short*)&(registerList[registerOrder]);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors. Wrong syntax";
	}

	char* temp = new char[255];
	int charCount = 0;
	while (line[posInLine] == ' ') posInLine++;
	while (line[posInLine] != '\0' && line[posInLine] != ' ') {
		temp[charCount] = line[posInLine];
		posInLine++;
		charCount++;
	}
	temp[charCount] = '\0';
	char* destination = new char[charCount + 1];
	strcpy(destination, temp);
	delete[] temp;
	this->destinationLabel = destination;
	while (line[posInLine] == ' ') posInLine++;
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void BeqInstruction::execute(int &commandAddr, LabelTable labelTable) {
	if ((*(this->rt)) == (*(this->rs))) {
		bool isLabelExisting = labelTable.checkLabelExist(this->destinationLabel);
		if (isLabelExisting) {
			Label* pCurLabel = labelTable.pFirst;
			while (pCurLabel != NULL)
			{
				if (strcmp(this->destinationLabel, pCurLabel->labelContent) == 0) break;
				pCurLabel = pCurLabel->pNext;
			}
			commandAddr = pCurLabel->addr;
		}
		else throw "Complete with errors. Wrong label";
	}
	else commandAddr++;
}

bool BneInstruction::check(char * line, int posInLine, RegisterList *& registerList)
{
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = (short*)&(registerList[registerOrder]);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors. Wrong syntax";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rt = (short*)&(registerList[registerOrder]);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors. Wrong syntax";
	}

	char* temp = new char[255];
	int charCount = 0;
	while (line[posInLine] == ' ') posInLine++;
	while (line[posInLine] != '\0' && line[posInLine] != ' ') {
		temp[charCount] = line[posInLine];
		posInLine++;
		charCount++;
	}
	temp[charCount] = '\0';
	char* destination = new char[charCount + 1];
	strcpy(destination, temp);
	delete[] temp;
	this->destinationLabel = destination;
	while (line[posInLine] == ' ') posInLine++;
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void BneInstruction::execute(int & commandAddr, LabelTable labelTable)
{
	if (((*(this->rt)) != (*(this->rs)))) {
		bool isLabelExisting = labelTable.checkLabelExist(this->destinationLabel);
		if (isLabelExisting) {
			Label* pCurLabel = labelTable.pFirst;
			while (pCurLabel != NULL)
			{
				if (strcmp(this->destinationLabel, pCurLabel->labelContent) == 0) break;
				pCurLabel = pCurLabel->pNext;
			}
			commandAddr = pCurLabel->addr;
		}
		else throw "Complete with errors. Wrong label";
	}
	else commandAddr++;
}

bool AddiInstruction::check(char * line, int posInLine, RegisterList*& registerList)
{
	int registerOrder;

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rt = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	this->imm = getAndCheckImmediate(line, posInLine);

	while (*(line + posInLine) == ' ') posInLine++;
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	throw "Completed with errors. Why do u come here";
	return false;
}

void AddiInstruction::execute(int & commandAddr, LabelTable labelTable)
{
	*(this->rt) = *(this->rs) + (this->imm);
	commandAddr++;
}

bool LiInstruction::check(char * line, int posInLine, RegisterList * registerList)
{
	int registerOrder = 0;
	// Get register from line
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rt = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Complete with errors. Syntax errors";
	}
	//Get imm from line
	this->imm = getAndCheckImmediate(line, posInLine);
	while (*(line + posInLine) == ' ') posInLine++;
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	throw "Complete with errors. Synotax errors";
	return false;
}

void LiInstruction::execute(int & commandAddr, LabelTable labelTabel)
{
	*(this->rt) = imm;
	commandAddr++;
}

bool JalInstruction::check(char * line, int _posInLine, LabelTable & tableLabel)
{
	while (line[_posInLine] == ' ') _posInLine++;
	char* temp = new char[255];								// Tempcontain the content of following text
	int count = 0;
	while (line[_posInLine] != '\0' && line[_posInLine] != ' ') {
		temp[count] = line[_posInLine];
		_posInLine++;
		count++;
	}
	temp[count] = '\0';
	while (line[_posInLine] == ' ') _posInLine++;
	if (line[_posInLine] != '\0') return false;
	this->destination = new char[count + 1];
	strcpy(this->destination, temp);
	return true;
}

void JalInstruction::execute(int & commandAddr, LabelTable labelTable, RegisterList* registerList)
{
	registerList->ra = commandAddr + 1;
	bool isLabelExisting = labelTable.checkLabelExist(this->destination);
	if (isLabelExisting) {
		Label* pCurLabel = labelTable.pFirst;
		while (pCurLabel != NULL)
		{
			if (strcmp(this->destination, pCurLabel->labelContent) == 0) break;
			pCurLabel = pCurLabel->pNext;
		}
		commandAddr = pCurLabel->addr;
	}
	else throw "Complete with errors. Wrong label";
}

bool SubInstruction::check(char * line, int posInLine, RegisterList *& registerList)
{
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rd = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rt = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void SubInstruction::execute()
{
	*rd = *rs - *rt;
}

bool JrInstruction::check(char * line, int posInLine, RegisterList *& registerList)
{
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->raAddr = *((short*)(registerList)+registerOrder);
	while (line[posInLine] == ' ') posInLine++;
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void JrInstruction::execute(int& commandAddr, RegisterList *& registerList)
{
	commandAddr = registerList->ra;
}

bool AndInstruction::check(char * line, int posInLine, RegisterList *& registerList)
{
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rd = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rt = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void AndInstruction::execute(int & commandAddr, RegisterList *& registerList)
{
	*rd = (*rs & *rt);
	commandAddr++;
}

bool NorInstruction::check(char * line, int posInLine, RegisterList *& registerList)
{
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rd = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rt = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void NorInstruction::execute(int & commandAddr, RegisterList *& registerList)
{
	*rd = ~(*rs | *rt);
	commandAddr++;
}

bool OrInstruction::check(char * line, int posInLine, RegisterList *& registerList)
{
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rd = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rt = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void OrInstruction::execute(int & commandAddr, RegisterList *& registerList)
{
	*rd = (*rs | *rt);
	commandAddr++;
}

bool SltInstruction::check(char * line, int posInLine, RegisterList *& registerList)
{
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rd = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rt = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void SltInstruction::execute(int & commandAddr, RegisterList *& registerList)
{
	*rs < *rt ? *rd = 1 : *rd = 0;
	commandAddr++;
}

bool SltuInstruction::check(char * line, int posInLine, RegisterList *& registerList)
{
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rd = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rt = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void SltuInstruction::execute(int & commandAddr, RegisterList *& registerList)
{ 
	int _rs = *rs;
	int _rt = *rt;
	if (_rs < 0) _rs = pow(2, 15) + _rs;
	if (_rt < 0) _rt = pow(2, 15) + _rt;
	_rs < _rt ? *rd = 1 : *rd = 0;
	commandAddr++;
}

bool SllInstruction::check(char * line, int posInLine, RegisterList *& registerList)
{
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rd = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}
	this->shiftAmount = getAndCheckImmediate(line, posInLine);
	while (*(line + posInLine) == ' ') posInLine++;
	this->rs = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void SllInstruction::execute(int & commandAddr, RegisterList *& registerList)
{
	if (this->shiftAmount < 0) throw "Complete with errors. Wrong shift amount.";
	*rd = *rs << shiftAmount;
	commandAddr++;
}

bool SrlInstruction::check(char * line, int posInLine, RegisterList *& registerList)
{
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rd = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}
	this->shiftAmount = getAndCheckImmediate(line, posInLine);
	while (*(line + posInLine) == ' ') posInLine++;
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void SrlInstruction::execute(int & commandAddr, RegisterList *& registerList)
{
	if (this->shiftAmount < 0) throw "Complete with errors. Wrong shift amount.";
	*rd = *rs >> shiftAmount;
	commandAddr++;
}

bool SubuInstruction::check(char * line, int posInLine, RegisterList *& registerList)
{
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rd = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rt = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void SubuInstruction::execute(int & commandAddr, RegisterList *& registerList)
{
	int _rs = *rs;
	int _rt = *rt;
	if (_rs < 0) _rs = pow(2, 15) + _rs;
	if (_rt < 0) _rt = pow(2, 15) + _rt;
	*rd = _rs - _rt;
	commandAddr++;
}

bool DivInstruction::check(char * line, int posInLine, RegisterList *& registerList)
{
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rd = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rt = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void DivInstruction::execute(int & commandAddr, RegisterList *& registerList)
{
		if (*rt == 0) throw "Complete with errors. Div by zero.";
		else *rd = *rs / *rt;
	commandAddr++;
}

bool DivuInstruction::check(char * line, int posInLine, RegisterList *& registerList)
{
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rd = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rt = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void DivuInstruction::execute(int & commandAddr, RegisterList *& registerList)
{
	int _rs = *rs;
	int _rt = *rt;
	if (_rs < 0) _rs = pow(2, 15) + _rs;
	if (_rt < 0) _rt = pow(2, 15) + _rt;
	if (_rt == 0) throw "Complete with errors. Divide by zero.";
	else *rd = (_rs) / (_rt);
	commandAddr++;
}

bool MultInstruction::check(char * line, int posInLine, RegisterList *& registerList)
{
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rd = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rt = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void MultInstruction::execute(int & commandAddr, RegisterList *& registerList)
{
	*rd = (*rs) * (*rt);
}

bool MultuInstruction::check(char * line, int posInLine, RegisterList *& registerList)
{
	int registerOrder;
	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rd = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rs = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == ',')
	{
		posInLine++;
	}
	else
	{
		throw "Completed with errors.";
	}

	registerOrder = getAndCheckRegisterName(line, posInLine);
	this->rt = &*((short*)(registerList)+registerOrder);
	if (*(line + posInLine) == '\0')
	{
		return true;
	}
	else
	{
		throw "Completed with errors.";
	}
	return true;
}

void MultuInstruction::execute(int & commandAddr, RegisterList *& registerList)
{
	int _rs = *rs;
	cout << _rs << endl;
	int _rt = *rt;
	cout << (_rt < 0 )<< endl;
	if (_rs < 0) _rs = pow(2, 15) + _rs;
	if (_rt < 0) _rt = pow(2, 15) + _rt;
	*rd = (_rs) * (_rt);
	commandAddr++;
}
