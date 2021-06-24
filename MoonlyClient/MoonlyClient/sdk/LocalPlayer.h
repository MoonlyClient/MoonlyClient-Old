#pragma once

#include <bitset>

#include "../utils/Utils.h"

class LocalPlayer : public Actor {
public:
	virtual void resolveDeathLoot(int param_1, class ActorDamageSource* param_2);
	virtual __int64 _guard_check_icall11();
	virtual void setSleeping(bool param_1);
	virtual void setSprinting(bool param_1);
	virtual void playAmbientSound();
	virtual class LevelSoundEvent* getAmbientSound();
	virtual class LevelSoundEvent* getHurtSound();
	virtual class LevelSoundEvent* getDeathSound();
	virtual int getAmbientSoundPostponeTicks();
	virtual int getAmbientSoundPostponeTicksRange();
	virtual class TextureUVCoordinateSet* getItemInHandIcon(class ItemStack* param_1, int param_2);
	virtual float getSpeed();
	virtual void setSpeed(float param_1);
	virtual float getJumpPower();
	virtual bool hurtEffects(class ActorDamageSource* param_1, int param_2, bool param_3, bool param_4);
	virtual int getMeleeWeaponDamageBonus(class Mob* param_1);
	virtual int getMeleeKnockbackBonus();
	virtual void travel(class IMobMovementProxy* param_1, float param_2, float param_3, float param_4);
	virtual void travel(float param_1, float param_2, float param_3);
	virtual void applyFinalFriction(float param_1, bool param_2);
	virtual void updateWalkAnim();
	virtual void aiStep(class IMobMovementProxy* param_1);
	virtual void aiStep();
	virtual void pushActors();
	virtual void lookAt(class Actor* param_1, float param_2, float param_3);
	virtual bool isLookingAtAnEntity();
	virtual bool checkSpawnRules(bool param_1);
	virtual bool checkSpawnObstruction();
	virtual float getAttackAnim(float param_1);
	virtual int getItemUseDuration();
	virtual float getItemUseStartupProgress();
	virtual float getItemUseIntervalProgress();
	virtual int getItemuseIntervalAxis();
	virtual int getTimeAlongSwing();
	virtual __int64 _guard_check_icall12();
	virtual float getMaxHeadXRot();
	virtual class Mob* getLastHurtByMob();
	virtual void setLastHurtByMob(class Mob* param_1);
	virtual class Player* getLastHurtByPlayer();
	virtual void setLastHurtByPlayer(class Player* param_1);
	virtual class Mob* getLastHurtMob();
	virtual void setLastHurtMob(class Actor* param_1);
	virtual __int64 getReturnPolicy8();
	virtual bool doHurtTarget(class Actor* param_1);
	virtual __int64 getReturnPolicy9();
	virtual void leaveCaravan();
	virtual void joinCaravan(class Mob* param_1);
	virtual bool hasCaravanTail();
	virtual class ActorUniqueID* getCaravanHead();
	virtual int getArmorValue();
	virtual float getArmorCoverPercentage();
	virtual void hurtArmor(class ActorDamageSource* param_1, int param_2, std::bitset<4>* param_3);
	virtual void hurtArmor(class ActorDamageSource* param_1, int param_2);
	virtual void hurtArmorSlot(class ActorDamageSource* param_1, int param_2, class ArmorSlot* param_3);
	virtual void setDamagedArmor(class ArmorSlot* param_1, class ItemStack* param_2);
	virtual __int64 _guard_check_icall13();
	virtual void sendArmor(std::bitset<4>* param_1);
	virtual void containerChanged(int param_1);
	virtual void updateEquipment();
	virtual int clearEquipment();
	virtual class std::vector<class ItemStack const*, class std::allocator<class ItemStack const*>> getAllArmor();
	virtual std::vector<int, class std::allocator<int>> getAllArmorID();
	virtual class std::vector<class ItemStackconst*, class std::allocator<class ItemStack const*>> getAllHand();
	virtual class std::vector<class ItemStack const*, class std::allocator<class ItemStack const*>> getAllEquipment();
	virtual int getArmorTypeHash();
	virtual void dropEquipmentOnDeath();
	virtual void dropEquipmentOnDeath(class ActorDamageSource* param_1, int param_2);
	virtual __int64 _guard_check_icall14();
	virtual __int64 _guard_check_icall15();
	virtual int getDamageAfterMagicAbsorb(class ActorDamageSource* param_1, int param_2);
	virtual bool createAIGoals();
	virtual __int64 _guard_check_icall16();
	virtual bool setItemSlot(class EquipmentSlot* param_1, class ItemStack* param_2);
	virtual void setTransitioningSitting(bool param_1);
	virtual void attackAnimation(class Actor* param_1, float param_2);
	virtual int getAttackTime();
	virtual __int64 stbir__support_zero1();
	virtual __int64 __vcrt_uninitialize14();
	virtual __int64 getReturnPolicy10();
	virtual void ascendLadder();
	virtual void ascendScaffolding0();
	virtual void ascendScaffolding1();
	virtual void descendScaffolding();
	virtual bool canAscendCurrentBlockByJumping();
	virtual void dropContainer();
	virtual class std::unique_ptr<class BodyControl, struct std::default_delete<class BodyControl>>* initBodyControl();
	virtual void jumpFromGround(class IMobMovementProxy* param_1);
	virtual void jumpFromGround();
	virtual __int64 _guard_check_icall17();
	virtual void newServerAiStep();
	virtual __int64 _guard_check_icall18();
	virtual int getDamageAfterEnchantReduction(class ActorDamageSource* param_1, int param_2);
	virtual int getDamageAfterArmorAbsorb(class ActorDamageSource* param_1, int param_2);
	virtual void dropBags();
	virtual void tickDeath();
	virtual void updateGliding();
	virtual __int64 __vcrt_uninitialize15();
	virtual void prepareRegion(class ChunkSource* param_1);
	virtual void destroyRegion();
	virtual void suspendRegion();
	virtual __int64 _guard_check_icall19();
	virtual void _fireWillChangeDimension();
	virtual void _fireDimensionChanged();
	virtual __int64 _guard_check_icall20();
	virtual int tickWorld(class Tick* param_1);

	/*
	inline void printToChat(std::string message) {
		TextHolder text = TextHolder(message);
		this->displayTextObjectMessage(&text);
	}*/
};
