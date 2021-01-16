#pragma once
#include "TextHolder.h"

class RakNetInstance {
private:
	char pad_0x0008[0x368];  //0x0000
public:
	TextHolder serverIp; //0x370

private:
	virtual ~RakNetInstance();
	virtual __int64 onAppResumed(void);
	virtual __int64 onAppSuspended(void);

public:
	virtual TextHolder* getLocalIps(TextHolder*);
	virtual TextHolder* getLocalIp(TextHolder*);

public:
	virtual unsigned int getPort(void) const;

private:
	virtual __int64 getRefinedLocalIps(void) const;
	virtual __int64 getConnectedGameInfo(void) const;

public:
	virtual void setupNatPunch(bool);

private:
	virtual __int64 getNatPunchInfo(void) const;
	virtual __int64 startNatPunchingClient(__int64);
	virtual __int64 addConnectionStateListener(__int64);
	virtual __int64 removeConnectionStateListener(__int64);

public:
	virtual bool isIPv4Supported(void) const;
	virtual bool isIPv6Supported(void) const;

private:
	virtual __int64 getIPv4Port(void) const;
	virtual __int64 getIPv6Port(void) const;
	virtual __int64 getGUID(void) const;
};
