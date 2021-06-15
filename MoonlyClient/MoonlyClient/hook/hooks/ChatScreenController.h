#pragma once

#include "../Hook.h"
#include "../../sdk/TextHolder.h"

class ChatScreenControllerHook : public Hook {
public:
	void install();
};

typedef void(__stdcall* sendMessage)(__int64);
sendMessage _sendMessage;

void sendMessage_callback(__int64 _this) {
	/* ToDo : Fix
	TextHolder* messageHolder = reinterpret_cast<TextHolder*>(_this + 0xA70);

	if (messageHolder->getTextLength() > 0) {
		char* message = messageHolder->getText();

		if (*message == '.' && messageHolder->getTextLength() > 1) {
			// ToDo

			//messageHolder->resetWithoutDelete();

			return;
		}
	}
	*/
	
	_sendMessage(_this);
}

void ChatScreenControllerHook::install() {
	this->hookSig("sendMessage", xorstr_("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B D9 48 83 B9"), &sendMessage_callback, reinterpret_cast<LPVOID*>(&_sendMessage));
}
