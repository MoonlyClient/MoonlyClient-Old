#pragma once

#include <vector>
#include "Hook.h"

class HookManager {
public:
	std::vector<Hook*> hooks;

	void init();
};

extern HookManager hookMgr;