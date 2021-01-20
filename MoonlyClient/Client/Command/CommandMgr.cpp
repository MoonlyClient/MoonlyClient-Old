#include "../../Other/Utils.h"
#include "CommandMgr.h"
#include "Commands/Command.h"

#undef min

#include "Commands/TestCommand.h"
#include "Commands/UninjectCommand.h"

void CommandMgr::Init() {

#if _DEBUG
	commands.push_back(new TestCommand());
	commands.push_back(new UninjectCommand());
#endif
}

std::vector<Command*> CommandMgr::getCommandList() {
	return commands;
}

void CommandMgr::execute(char* message) {
	if (message != nullptr) {
		std::vector<std::string> args;
		std::string msgStr = message + 1;
		size_t pos = msgStr.find(" "), initialPos = 0;

		while (pos != std::string::npos) {
			args.push_back(msgStr.substr(initialPos, pos - initialPos));
			initialPos = pos + 1;

			pos = msgStr.find(" ", initialPos);
		}

		args.push_back(msgStr.substr(initialPos, std::min(pos, msgStr.size()) - initialPos + 1));

		std::string cmd = args[0];
		std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

		for (auto it = commands.begin(); it != commands.end(); ++it) {
			Command* c = *it;

			Utils::DebugLogOutput("COMMAND : " + c->getName());

			if (c->getName() == cmd) {
				c->execute(args);
			}
		}
	}
}
