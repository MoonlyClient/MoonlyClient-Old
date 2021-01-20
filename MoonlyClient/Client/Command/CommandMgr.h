#pragma once
#include "../../Other/Utils.h"

class CommandMgr {
public:
	void Init();
	std::vector<class Command*> getCommandList();
	void execute(char* message);
	std::vector<class Command*> commands;
};