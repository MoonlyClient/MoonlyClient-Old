#pragma once
#include "../Other/Utils.h"

class ClientManager {
public:
	static void InitHooks();
	static void InitModules();
	static std::vector<class Hook*> Hooks;
	static std::vector<class Module*> Modules;
	static std::vector<std::string> Categories;

	static std::vector<class Module*> GetModulesFromCategory(std::string Category);
};