#pragma once

#include "Actor.h"
#include "LocalPlayer.h"

class GameMode {
public:
	LocalPlayer* Player; //0x0008

	virtual void Destructor();
	virtual void startDestroyBlock(Vec3_i* const&, unsigned char, bool &); // _ZN8GameMode17startDestroyBlockERK8BlockPoshRb
    virtual void destroyBlock(Vec3_i* const&, unsigned char); // _ZN8GameMode12destroyBlockERK8BlockPosh
    virtual void continueDestroyBlock(Vec3_i* const&, unsigned char, bool &); // _ZN8GameMode20continueDestroyBlockERK8BlockPoshRb
    virtual void stopDestroyBlock(Vec3_i* const&); // _ZN8GameMode16stopDestroyBlockERK8BlockPos
    virtual void startBuildBlock(Vec3_i* const&, unsigned char); // _ZN8GameMode15startBuildBlockERK8BlockPosh
    virtual void buildBlock(Vec3_i* const&, unsigned char); // _ZN8GameMode10buildBlockERK8BlockPosh
    virtual void continueBuildBlock(Vec3_i* const&, unsigned char); // _ZN8GameMode18continueBuildBlockERK8BlockPosh
    virtual void stopBuildBlock(); // _ZN8GameMode14stopBuildBlockEv
    virtual void tick(); // _ZN8GameMode4tickEv
//  virtual void getPickRange(InputMode const&, bool); //TODO: incomplete function definition // _ZN8GameMode12getPickRangeERK9InputModeb
    //virtual void useItem(ItemStack &); // _ZN8GameMode7useItemER9ItemStack
    //virtual void useItemOn(ItemStack &, BlockPos const&, unsigned char, Vec3 const&, Block const*); // _ZN8GameMode9useItemOnER9ItemStackRK8BlockPoshRK4Vec3PK5Block
    virtual void interact(Actor *, Vec3 const&); // _ZN8GameMode8interactER5ActorRK4Vec3
    virtual void attack(Actor *); // _ZN8GameMode6attackER5Actor
    virtual void releaseUsingItem(); // _ZN8GameMode16releaseUsingItemEv
    virtual void setTrialMode(bool); // _ZN8GameMode12setTrialModeEb
    virtual bool isInTrialMode(); // _ZN8GameMode13isInTrialModeEv
    virtual void registerUpsellScreenCallback(std::function<void (bool)>); // _ZN8GameMode28registerUpsellScreenCallbackESt8functionIFvbEE

    void _canDestroy(Vec3_i* const&, unsigned char); // _ZN8GameMode11_canDestroyERK8BlockPosh
    void _creativeDestroyBlock(Vec3_i* const&, unsigned char); // _ZN8GameMode21_creativeDestroyBlockERK8BlockPosh
    void _destroyBlockInternal(Vec3_i* const&, unsigned char); // _ZN8GameMode21_destroyBlockInternalERK8BlockPosh
    //void getDestroyRate(Block const&); // _ZN8GameMode14getDestroyRateERK5Block
    void _calculatePlacePos(Vec3_i* const&, unsigned char &)const; // _ZNK8GameMode18_calculatePlacePosERK8BlockPosRh
    bool isLastBuildBlockSnappable()const; // _ZNK8GameMode25isLastBuildBlockSnappableEv
    bool hasStartedBuilding()const; // _ZNK8GameMode18hasStartedBuildingEv
    bool hasContinueDirection()const; // _ZNK8GameMode20hasContinueDirectionEv
    void getContinueFacing()const; // _ZNK8GameMode17getContinueFacingEv
    void getContinueDirection()const; // _ZNK8GameMode20getContinueDirectionEv
    void getNextContinuePos()const; // _ZNK8GameMode18getNextContinuePosEv
    void getLastBuiltBlockPos()const; // _ZNK8GameMode20getLastBuiltBlockPosEv
    //void _canUseBlock(Block const&); // _ZN8GameMode12_canUseBlockERK5Block
    //void baseUseItem(ItemStack &); // _ZN8GameMode11baseUseItemER9ItemStack
    void getMaxPickRange(); // _ZN8GameMode15getMaxPickRangeEv
    void getMaxPickRangeSqr(); // _ZN8GameMode18getMaxPickRangeSqrEv
    void getDestroyBlockPos(); // _ZN8GameMode18getDestroyBlockPosEv
    void getOldDestroyProgress(); // _ZN8GameMode21getOldDestroyProgressEv
    void getDestroyProgress(); // _ZN8GameMode18getDestroyProgressEv
    void _releaseUsingItemInternal(); // _ZN8GameMode25_releaseUsingItemInternalEv
    void getHitProgress(float); // _ZN8GameMode14getHitProgressEf
};