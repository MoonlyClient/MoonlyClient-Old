#pragma once
#include "Command.h"

class TestCommand : public Command
{
public:
	TestCommand();
	virtual void execute(std::vector<std::string> args) override;
};

