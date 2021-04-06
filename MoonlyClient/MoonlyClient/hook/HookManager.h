#pragma once

#include <vector>
#include "Hook.h"

class HookManager {
public:
	std::vector<class Hook*> hooks;

	void init();
};

extern HookManager hookMgr;