#include "ModuleManager.h"

#include "modules/AutoSprint.h"
#include "modules/Compass.h"
#include "modules/Coords.h"
#include "modules/CPS.h"
#include "modules/FPS.h"
#include "modules/GUI.h"
#include "modules/Keystroke.h"
#include "modules/MenuGUI.h"
#include "modules/NightVision.h"
#include "modules/ReachDisplay.h"
#include "modules/Uninject.h"
#include "modules/Zoom.h"

ModuleManager moduleMgr;

void ModuleManager::init() {
	modules.push_back(new AutoSprint());
	modules.push_back(new Compass());
	modules.push_back(new Coords());
	modules.push_back(new CPS());
	modules.push_back(new FPS());
	modules.push_back(new GUI());
	modules.push_back(new Keystroke());
	modules.push_back(new MenuGUI());
	//modules.push_back(new NightVision());
	//modules.push_back(new ReachDisplay());
	//modules.push_back(new Uninject());
	//modules.push_back(new Zoom());

	for (int i = 0; i < modules.size(); i++) {
		bool exists = false;

		for (auto currCategory : categories) {
			if (currCategory == modules.at(i)->category)
				exists = true;
		}

		if (!exists) {
			categories.push_back(modules.at(i)->category);
		}
	}

	for (;;) {
		for (int i = 0; i < modules.size(); i++) {
			modules.at(i)->onLoop();
		}
	}
}

class Module* ModuleManager::getModuleByName(std::string name) {
	for (auto Module : modules) {
		if (Module->name == name) {
			return Module;
		}
	}

	return nullptr;
}

std::vector<class Module*> ModuleManager::getModulesFromCategory(std::string Category) {
	bool exists = false;
	for (auto Curr : categories) {
		if (Curr == Category)
			exists = true;
	}

	if (exists) {
		std::vector<Module*> modulesArr;

		for (auto Module : modules) {
			if (Module->category == Category)
				modulesArr.push_back(Module);
		}

		return modulesArr;
	}
	else {
		return std::vector<Module*>();
	}
}