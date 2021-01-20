#include "TestCommand.h"
#include "../../../SDK/Minecraft.h"

TestCommand::TestCommand() : Command("test", "Testing") {}

void TestCommand::execute(std::vector<std::string> args)
{
	C_GuiData* guiData = Minecraft::ClientInstance()->getGuiData();

	if (guiData != nullptr) {
		guiData->displayClientMessage("Testing lmao");
	}
}
