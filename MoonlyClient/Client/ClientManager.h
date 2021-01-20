#pragma once
#include "../Other/Utils.h"
#include "Command/CommandMgr.h"

class ClientManager {
public:
	static void InitHooks();
	static void InitModules();
	static std::vector<class Hook*> Hooks;
	static std::vector<class Module*> Modules;
	static std::vector<std::string> Categories;
	static CommandMgr* CmdMgr;

	static class Module* GetModuleByName(std::string name);
	static std::vector<class Module*> GetModulesFromCategory(std::string Category);
};