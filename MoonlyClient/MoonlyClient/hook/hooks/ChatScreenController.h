#pragma once
#include "../../Other/Module.h"

class ChatScreenController_Hook : public Hook {
public:
	void Install();
};

typedef void(__stdcall* sendMessage)(uint8_t*);
sendMessage _sendMessage;

void sendMessageCallback(uint8_t* _this) {
	TextHolder* messageHolder = reinterpret_cast<TextHolder*>(_this + 0xA70);

	if (messageHolder->getTextLength() > 0) {
		char* message = messageHolder->getText();

		if (*message == '.' && messageHolder->getTextLength() > 1) {
			ClientManager::CmdMgr->execute(message);

			messageHolder->resetWithoutDelete();
			return;
		}
	}

	_sendMessage(_this);
}

void ChatScreenController_Hook::Install() {
	uintptr_t sigAddr = Utils::FindSig("48 89 5C 24 08 57 48 83 EC ?? 48 8B D9 48 83 B9");
	if (sigAddr) {
		Utils::DebugLogOutput("Found address needed for the sendMessageCallback Hook, Preparing Hook install now...");
		if (MH_CreateHook((void*)sigAddr, &sendMessageCallback, reinterpret_cast<LPVOID*>(&_sendMessage)) == MH_OK) {
			Utils::DebugLogOutput("Successfully created sendMessageCallback Hook, Installing Hook now...");
			MH_EnableHook((void*)sigAddr);
		}
		else {
			Utils::DebugLogOutput("Failed to create sendMessageCallback Hook!");
		}
	}
	else {
		Utils::DebugLogOutput("Failed to find address needed for the sendMessageCallback Hook!");
	}
}