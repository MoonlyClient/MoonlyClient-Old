#include "Module.h"

Module::Module(std::string name, std::string category, std::string description, uint64_t key) {
	this->name = name;
	this->category = category;
	this->description = description;
	this->key = key;
}