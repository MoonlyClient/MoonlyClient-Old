#pragma once

#include <string>

class ItemStack {
public:
	virtual void* UndefinedFunc_0(void* param_1);
	virtual void reinit(std::string param_1, int param_2, int param_3);
	virtual void reinit(class BlockLegacy* param_1, int param_2);
	virtual void reinit(class Item* param_1, int param_2, int param_3);
	virtual void setNull();
	virtual std::string* toString();
	virtual std::string* toDebugString();
};