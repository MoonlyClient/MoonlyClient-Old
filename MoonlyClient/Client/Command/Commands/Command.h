#pragma once
#include "../../../Other/Utils.h"

class Command {
public:
	std::string name, description;
	Command(std::string name, std::string description);

	virtual std::string getName() { return this->name; }
	virtual void execute(std::vector<std::string> args) {};
};