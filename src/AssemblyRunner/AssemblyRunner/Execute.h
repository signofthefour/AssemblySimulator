#pragma once
#ifndef _EXECUTE_
#define _EXECUTE_
#include "Command.h"
#include "Label.h"

void execute(CommandLine** &commandTable, LabelTable labelTable, RegisterList* registerList);
void finitialize(CommandLine*& commandTable, LabelTable*& labelTable, RegisterList*& registerList);

#endif // !_EXECUTE_
