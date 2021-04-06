#pragma once

#include "Module.h"

class ModuleManager {
public:
	std::vector<class Module*> modules;
	std::vector<std::string> categories;

	// Command manager

	void init();
	class Module* getModuleByName(std::string name);
	std::vector<class Module*> getModulesFromCategory(std::string Category);
};

extern ModuleManager moduleMgr;