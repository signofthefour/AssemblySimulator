#include "Execute.h"
#include "Command.h"

void execute(CommandLine** &commandTable, LabelTable labelTable, RegisterList* registerList)
{
int commandAddr = 0;
	do
	{
		commandAddr = registerList->pc;
		switch (commandTable[commandAddr]->rType.opcode) {
		case ADD:
		{
			AddInstruction* pExCommand = new AddInstruction;
			pExCommand = (AddInstruction*)&(commandTable[commandAddr]->rType);
			pExCommand->execute();
			commandAddr++;
			break;
		}
		case SUB:
		{
			SubInstruction* pExCommand = new SubInstruction;
			pExCommand = (SubInstruction*)&(commandTable[commandAddr]->rType);
			pExCommand->execute();
			commandAddr++;
			break;
		}
		case J:
		{
			JumpInstruction* pExCommand = new JumpInstruction;
			pExCommand = (JumpInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, labelTable);
			break;
		}
		case BEQ:
		{
			BeqInstruction* pExCommand = new BeqInstruction;
			pExCommand = (BeqInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, labelTable);
			break;
		}
		case BNE:
		{
			BneInstruction* pExCommand = new BneInstruction;
			pExCommand = (BneInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, labelTable);
			break;
		}
		case ADDI:
		{
			AddiInstruction* pExCommand = new AddiInstruction;
			pExCommand = (AddiInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, labelTable);
			break;
		}
		case LI:
		{
			LiInstruction* pExCommand = new LiInstruction;
			pExCommand = (LiInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, labelTable);
			break;
		}
		case JAL:
		{
			JalInstruction* pExCommand = new JalInstruction;
			pExCommand = (JalInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, labelTable, registerList);
			break;
		}
		case JR:
		{
			JrInstruction* pExCommand = new JrInstruction;
			pExCommand = (JrInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, registerList);
			break;
		}
		case AND:
		{
			AndInstruction* pExCommand = new AndInstruction;
			pExCommand = (AndInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, registerList);
			break;
		}
		case NOR:
		{
			NorInstruction* pExCommand = new NorInstruction;
			pExCommand = (NorInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, registerList);
			break;
		}
		case OR:
		{
			OrInstruction* pExCommand = new OrInstruction;
			pExCommand = (OrInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, registerList);
			break;
		}
		case SLT:
		{
			SltInstruction* pExCommand = new SltInstruction;
			pExCommand = (SltInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, registerList);
			break;
		}
		case SLTU:
		{
			SltuInstruction* pExCommand = new SltuInstruction;
			pExCommand = (SltuInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, registerList);
			break;
		}
		case SLL:
		{
			SllInstruction* pExCommand = new SllInstruction;
			pExCommand = (SllInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, registerList);
			break;
		}
		case SRL:
		{
			SrlInstruction* pExCommand = new SrlInstruction;
			pExCommand = (SrlInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, registerList);
			break;
		}
		case SUBU:
		{
			SubuInstruction* pExCommand = new SubuInstruction;
			pExCommand = (SubuInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, registerList);
			break;
		}
		case DIV:
		{
			DivInstruction* pExCommand = new DivInstruction;
			pExCommand = (DivInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, registerList);
			break;
		}
		case DIVU:
		{
			DivuInstruction* pExCommand = new DivuInstruction;
			pExCommand = (DivuInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, registerList);
			break;
		}
		case MULT:
		{
			MultInstruction* pExCommand = new MultInstruction;
			pExCommand = (MultInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, registerList);
			break;
		}
		case MULTU:
		{
			MultuInstruction* pExCommand = new MultuInstruction;
			pExCommand = (MultuInstruction*)&(commandTable[commandAddr]->jType);
			pExCommand->execute(commandAddr, registerList);
			break;
		}
		default:
			cout << "Out of command" << endl;
			system("pause");
			throw "completed with errors.";
			break;
		}
		registerList->pc = commandAddr;
		registerList->printAllRegister();
		system("pause");
		system("cls");
	} while (commandTable[commandAddr] != NULL);
}

void finitialize(CommandLine*& commandTable, LabelTable*& labelTable, RegisterList*& registerList) {
	delete[] commandTable;
	delete[] labelTable;
	delete[] registerList;
	commandTable = NULL;
	labelTable = NULL;
	registerList = NULL;
}