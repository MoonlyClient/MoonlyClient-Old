#pragma once

class LoopbackPacketSender {
public:
	virtual ~LoopbackPacketSender();
	//virtual __int64 send(Packet* packet);
	//virtual __int64 sendToServer(Packet* packet);
	//virtual __int64 sendToClient(const void* networkIdentifier, const Packet* packet, int a4);
	//virtual __int64 sendBroadcast(const Packet* packet);
	//virtual __int64 sendBroadcast(const void* networkIdentifier, int a3, const Packet* packet);
	virtual __int64 flush(void* networkIdentifier, int a3);
};