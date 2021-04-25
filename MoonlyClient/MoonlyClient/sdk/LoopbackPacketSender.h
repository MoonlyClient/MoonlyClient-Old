#pragma once

class LoopbackPacketSender {
public:
	virtual void* UndefinedFunc_0(void* param_1);
	virtual void send(class Packet* param_1);
	virtual void sendToServer(class Packet* param_1);
	virtual void sendToClient(class NetworkIdentifier* param_1, class Packet* param_2, unsigned char param_3);
	virtual void sendToClients(__int64* param_1, class Packet* param_2);
	virtual void sendBroadcast(class NetworkIdentifier* param_1, unsigned char param_2, class Packet* param_3);
	virtual void sendBroadcast(class Packet* param_1);
	virtual void flush(class NetworkIdentifier* param_1, std::function<void(void)>* param_2);
	virtual void* UndefinedFunc_8(void* param_1);
};