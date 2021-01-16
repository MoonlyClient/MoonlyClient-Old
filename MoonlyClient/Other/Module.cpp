#include "Module.h"

Module::Module(std::string name, std::string category, std::string description, uint64_t key) {
	this->name = name;
	this->category = category;
	this->description = description;
	this->key = key;
}

void Module::onBaseTick() {
	onLoop();
	if (wasEnabled != isEnabled) {
		if (isEnabled) {
			onEnable();
		}
		else {
			onDisable();
		}
		wasEnabled = isEnabled;
	}
	if (isEnabled) onTick();
}