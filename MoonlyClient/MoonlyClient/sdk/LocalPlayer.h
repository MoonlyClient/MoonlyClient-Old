#pragma once

class LocalPlayer : public Actor {
public:
	virtual void resolveDeathLoot(int param_1, class ActorDamageSource* param_2);
	virtual void _guard_check_icall14();
	virtual void setSleeping(bool param_1);
	virtual void setSprinting(bool param_1);
	virtual void playAmbientSound();
	virtual class LevelSoundEvent* getAmbientSound();
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

	// ToDo : Add others
};