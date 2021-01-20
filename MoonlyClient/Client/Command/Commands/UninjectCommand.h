#pragma once
#include "Command.h"

class UninjectCommand : public Command
{
public:
	UninjectCommand();
	virtual void execute(std::vector<std::string> args) override;
};

