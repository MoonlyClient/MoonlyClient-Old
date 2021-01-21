#include "UninjectCommand.h"
#include "../../../SDK/Minecraft.h"

UninjectCommand::UninjectCommand() : Command("uninject", "uninject") {}

void UninjectCommand::execute(std::vector<std::string> args)
{
	C_GuiData* guiData = Minecraft::ClientInstance()->getGuiData();

	if (guiData != nullptr) {
		guiData->displayClientMessage("Uninjecting...");

		Utils::running = false;
	}
}
