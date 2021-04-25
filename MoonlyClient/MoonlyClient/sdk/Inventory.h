#pragma once

#include<string>
#include<vector>
#include <functional>

class Inventory {
public:
	virtual void* UndefinedFunc_0(void* param_1);
	virtual void init();
	virtual void serverInitItemStackIds(int param_1, int param_2, std::function<void(int, class ItemStack const& ___ptr64)>* param_3);
	virtual void addContentChangeListener(class ContainerContentChangeListener* param_1);
	virtual void removeContentChangeListener(class ContainerContentChangeListener* param_1);
	virtual class ItemStack* getItem(int param_1);
	virtual bool hasRoomForItem(class ItemStack* param_1);
	virtual void addItem(class ItemStack* param_1);
	virtual bool addItemToFirstEmptySlot(class ItemStack* param_1);
	virtual void setItem(int param_1, class ItemStack* param_2);
	virtual void setItemWithForceBalance(int param_1, class ItemStack* param_2, bool param_3);
	virtual void removeItem(int param_1, int param_2);
	virtual void removeAllItems();
	virtual void dropContents(class BlockSource* param_1, class Vec3* param_2, bool param_3);
	virtual int getContainerSize();
	virtual int getMaxStackSize();
	virtual void _guard_check_icall1();
	virtual void _guard_check_icall2();
	virtual __int64* getSlotCopies();
	virtual __int64 getSlots();
	virtual int getItemCount(class ItemStack* param_1);
	virtual int findFirstSlotForItem(class ItemStack* param_1);
	virtual __int64 __vcrt_uninitialize1();
	virtual __int64 __vcrt_uninitialize2();
	virtual void setContainerChanged(int param_1);
	virtual void setContainerMoved();
	virtual void setCustomName(std::string* param_1);
	virtual bool hasCustomName();
	virtual void readAdditionalSaveData(class CompoundTag* param_1);
	virtual void addAdditionalSaveData(class CompoundTag* param_1);
	virtual void createTransactionContext(class std::function<void(class Container&, int, class ItemStack const&, class ItemStack const&)>* param_1, std::function<void(void)> param_2);
	virtual void _guard_check_icall();
	virtual bool isEmpty();
	virtual bool add(class ItemStack* param_1);
	virtual bool canAdd(class ItemStack* param_1);
	virtual void clearSlot(int param_1);
	virtual int clearInventory(int param_1);
	virtual void load(class ListTag* param_1, class SemVersion* param_2, class Level* param_3);
	virtual int getEmptySlotsCount();
	virtual int getFirstEmptySlot();
	virtual void setContainerSize(int param_1);
};