#pragma once
#ifndef _COMMAND_
#define _COMMAND_

#include <iostream>
#include "Register.h"
#include "Label.h"

using namespace std;

#define	J		0
#define	JAL		1
#define ADD		2			
#define JR		3	
#define AND		4	
#define NOR		5	
#define OR		6	
#define SLT		7	
#define SLTU	8
#define SLL		9
#define	SRL		10
#define	SUB		11
#define	SUBU	12
#define	DIV		13
#define	DIVU	14
#define	MULT	15
#define MULTU	16
#define	ADDI	17
#define	ADDIU	18
#define	ANDI	19
#define	BEQ		20
#define	BNE		21
#define	LBU		22
#define	LHU		23
#define	LL		24
#define	LUI		25
#define	LW		26
#define	ORI		27
#define	SLTI	28
#define	SLTUI	29
#define	SB		30
#define	SW		31
#define	LI		32

struct Command
{
	int opcode;
	virtual void execute() = 0;
	virtual bool check() = 0;
};

struct RTypeCommand : public Command
{
	short* rt;
	short* rd;
	short* rs;
	short* shamt;
	short* funct;
	void execute() {};
	bool check() { return true; };
};

struct ITypeCommand : public Command
{
	short* rt;
	short* rs;
	short imm;
	void execute() {};
	bool check() { return false; };
};

struct JTypeCommand : public Command
{
	uint32_t addr;
	void execute() {};
	bool check() { return false; };
};

union Pseudo
{
	RTypeCommand rPseudo;
	ITypeCommand iPseudo;
};

// Hierachy command of i, j, r type

struct AddInstruction : public RTypeCommand
{
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute();
};

struct SubInstruction : public RTypeCommand
{
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute();
};

struct JumpInstruction : public JTypeCommand
{
	char* destination;
	bool check(char* line, int posInLine, LabelTable& tableLabel);
	void execute(int &commandAddr, LabelTable labelTable);
};

struct JalInstruction : public JTypeCommand
{
	char* destination;
	bool check(char* line, int _posInLine, LabelTable& tableLabel);
	void execute(int &commandAddr, LabelTable labelTable, RegisterList* registerList);
};

struct JrInstruction : public RTypeCommand
{
	int raAddr;
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute(int &commandAddr, RegisterList*& registerList);
};

struct AndInstruction : public RTypeCommand
{
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute(int &commandAddr, RegisterList*& registerList);
};

struct NorInstruction  : public RTypeCommand
{
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute(int &commandAddr, RegisterList*& registerList);
};

struct OrInstruction : public RTypeCommand 
{
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute(int &commandAddr, RegisterList*& registerList);
};

struct SltInstruction : public RTypeCommand
{
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute(int &commandAddr, RegisterList*& registerList);
};

struct SltuInstruction : public RTypeCommand {
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute(int &commandAddr, RegisterList*& registerList);
};

struct SllInstruction : RTypeCommand {
	short shiftAmount;
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute(int &commandAddr, RegisterList*& registerList);
};

struct SrlInstruction : public RTypeCommand
{
	short shiftAmount;
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute(int &commandAddr, RegisterList*& registerList);
};

struct SubuInstruction : public RTypeCommand
{
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute(int &commandAddr, RegisterList*& registerList);
};

struct DivInstruction : public RTypeCommand
{
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute(int &commandAddr, RegisterList*& registerList);
};

struct DivuInstruction : public RTypeCommand
{
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute(int &commandAddr, RegisterList*& registerList);
};

struct MultInstruction : public RTypeCommand
{
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute(int &commandAddr, RegisterList*& registerList);
};

struct MultuInstruction :public RTypeCommand
{
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute(int &commandAddr, RegisterList*& registerList);
};

struct AddiInstruction : public ITypeCommand
{
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute(int &commandAddr, LabelTable labelTable);
};

struct BeqInstruction : public ITypeCommand
{
	char* destinationLabel;
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute(int &commandAddr, LabelTable labelTable);
};

struct BneInstruction : public ITypeCommand
{
	char* destinationLabel;
	bool check(char* line, int posInLine, RegisterList*& registerList);
	void execute(int &commandAddr, LabelTable labelTable);
};

struct LiInstruction : public ITypeCommand
{
	bool check(char* line, int posInLine, RegisterList* registerList);
	void execute(int& commandAddr, LabelTable labelTabel);
};

union CommandLine
{
	CommandLine() {};
	RTypeCommand rType;
	ITypeCommand iType;
	JTypeCommand jType;
	Pseudo pseudoType;
};

struct CommandNode
{
	CommandLine* pCommandLine;
	CommandNode* pNext;
	CommandNode(CommandLine* _pCommandLine) 
	{
		this->pNext = NULL;
		this->pCommandLine = _pCommandLine;
	}
};

struct CommandLinkedList
{
	CommandNode* pFirst;
	CommandNode* pLast;
	CommandLinkedList();
	void addCommand(CommandNode* newNode);
};

bool isCommand(char* line, int& commandAddr, RegisterList*& registerList, LabelTable& labelTabel);
CommandLine* checkCommand(int opcodeID, char* line, int posInLine, RegisterList*& registerList, LabelTable& labelTabel, int commandAddr);
void createCommandTable(CommandLine** &commandTable);

#endif // !_COMMAND_
