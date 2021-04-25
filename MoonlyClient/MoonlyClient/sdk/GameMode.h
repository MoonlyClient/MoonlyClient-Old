#pragma once

#include "Actor.h"
#include "LocalPlayer.h"

class GameMode {
public:
	LocalPlayer* Player; //0x0008

	virtual void* deconstructor(void* param_1);
	virtual bool startDestroyBlock(class BlockPos* param_1, unsigned char param_2, bool* param_3);
	virtual bool destroyBlock(class BlockPos* param_1, unsigned char param_2);
	virtual bool continueDestroyBlock(class BlockPos* param_1, unsigned char param_2, struct Vec3* param_3, bool* param_4);
	virtual void stopDestroyBlock(class BlockPos* param_1);
	virtual void startBuildBlock(class BlockPos* param_1, unsigned char param_2);
	virtual bool buildBlock(class BlockPos* param_1, unsigned char param_2);
	virtual void continueBuildBlock(class BlockPos* param_1, unsigned char param_2);
	virtual void stopBuildBlock();
	virtual void tick();
	virtual float getPickRange(class InputMode* param_1, bool param_2);
	virtual bool useItem(class ItemStack* param_1);
	virtual bool useItemOn(class ItemStack* param_1, class BlockPos* param_2, unsigned char param_3, struct Vec3* param_4, class Block* param_5);
	virtual bool interact(class Actor* param_1, struct Vec3* param_2);
	virtual bool attack(class Actor* param_1);
	virtual void releaseUsingItem();
	virtual void _guard_check_icall1();
	virtual bool getReturnPolicy1();
	virtual void exitVRMode(__int64);
	virtual void* UndefinedFunc_19(void* param_1);
	virtual void _guard_check_icall2();
	virtual void serverInitItemStackIds(int param_1, int param_2, __int64 param_3);
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
	virtual void dropContents(class BlockSource* param_1, struct Vec3* param_2, bool param_3);
	virtual int getContainerSize();
	virtual int getMaxStackSize();
	virtual void _guard_check_icall3();
	virtual void _guard_check_icall4();
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
	virtual void createTransactionContext(__int64* param_1, __int64 param_2);
	virtual void _guard_check_icall5();
	virtual bool isEmpty();
	virtual bool add(class ItemStack* param_1);
	virtual bool canAdd(class ItemStack* param_1);
	virtual void clearSlot(int param_1);
	virtual int clearInventory(int param_1);
	virtual void load(class ListTag* param_1, class SemVersion* param_2, class Level* param_3);
	virtual int getEmptySlotsCount();
	virtual void* UndefinedFunc_58(void* param_1);
	virtual bool isAsync();
};