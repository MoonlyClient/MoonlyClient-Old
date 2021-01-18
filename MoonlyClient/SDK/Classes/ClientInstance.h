#pragma once
#include "TextHolder.h"
#include "MinecraftUIRenderContext.h"
#include "Actor.h"
#include "LocalPlayer.h"
#include "GameMode.h"
#include "GuiData.h"
#include "GameSettingsInput.h"
#include "LoopbackPacketSender.h"


class C_Minecraft {
private:
	char pad_0x0000[0xB0];  //0x0000
public:
	float* timer;  //0x00B0
};

class BlockTessellator;

class ResourceLocation {
private:
	char pad[0x28];
	__int64 hashCode; // 0x28
	char pad2[8];
};

namespace mce {
	class TextureGroup;
	class MaterialPtr;
	class Mesh {
	public:
		void renderMesh(__int64 screenContext, mce::MaterialPtr* material, size_t numTextures, __int64** textureArray);

		template <size_t numTextures>
		void renderMesh(__int64 screenContext, mce::MaterialPtr* material, std::array<__int64*, numTextures> textures) {
			this->renderMesh(screenContext, material, numTextures, &textures[0]);
		}
	};
	class TexturePtr {
	private:
		__int64* clientTexture;
		char pad[0x8];
		ResourceLocation resourceLocation; // 0x10

	public:
		__int64* getClientTexture() {
			return this->clientTexture;
		}
	};
	class MaterialPtr {
	private:
		std::shared_ptr<void> materialPtr;

	public:
		MaterialPtr(const std::string& materialName);
	};
};


class LevelRenderer {
private:
	char pad_0x0000[0x58];  //0x0000
public:
	mce::TextureGroup* textureGroup; // 0x0058
private:
	char pad_0x0060[0xE0];  //0x0060
public:
	mce::TexturePtr atlasTexture; // 0x140
private:
	char pad_0x0188[0x150];  //0x0188
public:
	BlockTessellator* blockTessellator; // 0x02D8
private:
	char pad_0x02F0[0x5EC];  //0x02E0
public:
	Vec3 origin;  //0x0890

	__int64 getLevelRendererPlayer() {
		return reinterpret_cast<__int64>(this) + 0x310;
	}
};

class MinecraftGame {
public:
	class BitmapFont* MCFont() {
		return *reinterpret_cast<class BitmapFont**>(reinterpret_cast<__int64>(this) + 0xD8);
	}

	bool canUseKeys() {
		return *(bool*)(reinterpret_cast<uintptr_t>(this) + 0x260);
	}
};

struct PtrToGameSettings3 {
private:
	char pad_0x0000[0x18];
public:
	GameSettingsInput* settingsInput;
};

struct PtrToGameSettings2 {
private:
	char pad_0x0000[0x148];
public:
	PtrToGameSettings3* ptr;
};

struct PtrToGameSettings1 {
private:
	char pad_0x0000[0x18];
public:
	PtrToGameSettings2* ptr;
};

class ClientInstance {
private:
	char firstPad[0x90];  //0x0008
public:
	MinecraftGame* minecraftGame;  //0x0098
private:
	MinecraftGame* N0000080C;  //0x00A0
public:
	MinecraftGame* N0000080D;  //0x00A8
public:
	C_Minecraft* minecraft;  //0x00B0
private:
	char pad_0x0068[0x8];  //0x00B8
public:
	LevelRenderer* levelRenderer;  //0x00C0
private:
	char pad_0x0078[0x8];  //0x00C8
public:
	LoopbackPacketSender* loopbackPacketSender;  //0x00D0
private:
	char pad_0x0088[0x18];  //0x00D8
public:
	PtrToGameSettings1* ptr;  //0x00F0

private:
	virtual __int64 destructorClientInstance();
	// Duplicate destructor
	virtual __int64 onInitMinecraftGame(void);
	virtual __int64 onDestroyMinecraftGame(void);
	virtual __int64 init(__int64*, __int64&, __int64&, __int64&, __int64&, int);
	virtual __int64 initSceneFactory(__int64*);
	virtual __int64 initGraphics(void);
	virtual __int64 stop(void);
	virtual __int64 teardown(void);
	virtual __int64 preShutDown(void);
	virtual __int64 requestLeaveGame(bool, bool);
	virtual __int64 stopPlayScreen(void);

public:
	virtual bool isLeaveGameDone(void) const;
	virtual void setupPlayScreenForLeaveGame(void);

private:
	virtual __int64 resetPrimaryClient(void);
	virtual __int64 resetGameSession(void);
	virtual __int64 tick(void);
	virtual __int64 frameUpdate(__int64&);
	virtual __int64 update(bool);
	virtual __int64 endFrame(void);
	virtual __int64 startSubClientLateJoin(bool);

public:
	virtual void setupClientGame(__int64&&, bool);

private:
	virtual __int64 sub_1400C5D00(void) const;
	virtual __int64 getLocalC_Player(void);
	virtual __int64 getLocalC_Player(void) const;
	virtual __int64 getCameraEntity(void) const;

public:
	virtual void setCameraEntity(Actor*);

private:
	virtual __int64 getCameraTargetEntity(void) const;

public:
	virtual void setCameraTargetEntity(Actor*);
	virtual bool isLeavingGame(void) const;
	virtual bool isDestroyingGame(void) const;

private:
	virtual __int64 sub_1400C98E0(void) const;
	virtual __int64 useLowFrequencyUIRender(void) const;

public:
	virtual bool isSplitScreenActive(void) const;
	virtual bool isVRClient(void) const;
	virtual bool isARClient(void) const;
	virtual bool isARVRClient(void) const;
	virtual bool isHoloviewerMode(void) const;
	virtual bool isHoloscreenMode(void) const;
	virtual bool isLivingroomMode(void) const;
	virtual bool isExitingLevel(void) const;
	virtual bool isNotVLRMode(void) const;
	virtual bool isHoloRealityMode(void) const;
	virtual bool isRealityFullVRMode(void) const;
	virtual bool isInBedScreen(void) const;
	virtual bool isKeyboardEnabled(void) const;
	virtual bool isVRTransitioning(void) const;
	virtual bool hasCommands(void) const;
	virtual bool isScriptingEnabled(void) const;

private:
	virtual __int64 getHoloviewerScale(void) const;
	virtual __int64 getSplitScreenCount(void) const;

public:
	virtual bool isStereoRendering(void) const;
	virtual bool isPlatformNX(void) const;
	virtual bool isLocalSplitscreenWith(__int64 const&) const;
	virtual bool isValidCrossPlatformSkin(void) const;
	virtual __int64 sub_1400C9B70(void);

private:
	virtual __int64 getSplitScreenInfo(void) const;
	virtual __int64 getCurrentMaxGUIScaleIndex(void) const;
	virtual __int64 getRealityModeFrameFactor(void) const;

public:
	virtual void setRealityModeFrameFactor(float const&);

private:
	virtual __int64 getRealityModeToggleTriggered(void) const;

public:
	virtual void setRealityModeToggleTriggered(bool);

private:
	virtual bool sub_1400C9C50(void);

public:
	virtual void setOpenControllerDisconnectScreen(bool);

private:
	virtual __int64 getClientPlayMode(void) const;

public:
	virtual void setClientPlayMode(__int64 const&);

private:
	virtual __int64 getLivingRoomForCredits(void) const;

public:
	virtual void setLivingRoomForCredits(bool);

private:
	virtual __int64 getCreditsCallback(void);

public:
	virtual void setCreditsCallback(__int64);
	virtual void setupTransitionForCredits(__int64);

private:
	virtual __int64 refreshScreenSizeData(void);
	virtual __int64 onScreenSizeChanged(int, int, float);
	virtual __int64 onGuiScaleOffsetChanged(void);
	virtual __int64 onSafeZoneChanged(void);
	virtual __int64 quit(std::string const&, std::string const&);

public:
	virtual __int64 getMinecraftGame(void) const;

private:
	virtual __int64 getAutomationClient(void) const;
	virtual __int64 getScreenshotStreamer(void) const;
	virtual __int64 getEventing(void) const;
	virtual __int64 sub_1400CA2E0(__int64 a1);
	virtual __int64 sub_1400CA2E8(__int64 a1);
	virtual __int64 sub_1400CA2F0(__int64 a1);
	virtual BitmapFont* getFont(void) const;
	virtual BitmapFont* getRuneFont(void) const;
	virtual BitmapFont* getUnicodeFont(void) const;
	virtual __int64 getGeometryGroup(void) const;
	virtual __int64 getMultiplayerServiceManager(void) const;
	virtual __int64 getLocalServerLevel(void);
	virtual __int64 getResourcePackRepository(void) const;
	virtual __int64 getResourcePackManager(void) const;
	virtual __int64 getSkinRepository(void) const;
	virtual __int64 getSkinRepositoryClientInterface(void) const;
	virtual __int64 sub_140630650(void) const;
	virtual __int64 sub_1400CA400(void) const;
	virtual __int64 getTextures(void) const;
	virtual __int64 getStoreCacheTextures(void) const;
	virtual __int64 getMinecraftGraphics(void) const;
	virtual __int64 getUIRepository(void) const;
	virtual __int64 getUserManager(void) const;
	virtual __int64 wantToQuit(void) const;

public:
	virtual bool isPrimaryLevelCrossPlatformMultiplayer(void) const;
	virtual bool isPrimaryLevelMultiplayer(void) const;
	virtual bool isAdhocEnabled(void) const;

private:
	virtual __int64 linkToOffer(std::string const&, bool, std::string const&, __int64);
	virtual __int64 linkToAllOffers(std::string const&, std::string const&, bool, std::string const&, bool);
	virtual __int64 navigateToBrazeScreen(std::string const&, std::string const&, std::string const&, std::string const&, std::string const&, std::string const&, std::string const&);
	virtual __int64 navigateToStoreHomeScreen(void);
	virtual __int64 navigateToCoinPurchaseScreen(int, __int64);
	virtual __int64 navigateToPurchaseOfferScreen(__int64, bool);
	virtual __int64 navigateToOfferCollectionScreen(__int64&);
	virtual __int64 navigateToStoreSeeAllByCreatorScreen(std::string const&, bool);
	virtual __int64 navigateToServersScreen(bool);
	virtual __int64 navigateToHowToPlayScreen(std::string const&);
	virtual __int64 tryPushLeaveGameScreen(void);
	virtual char sub_1400D16A0(void) const;

public:
	virtual bool isReadyToRender(void) const;

private:
	virtual __int64 onDimensionChanged(void);
	virtual __int64 onGameEventNotification(__int64);

public:
	virtual TextHolder getTopScreenName(void) const;
	virtual void setLeaveGameInProgressAsReadyToContinue(void);

private:
	virtual __int64 stopDestroying(void);
	virtual __int64 onClientCreatedLevel(__int64);
	virtual __int64 getClientRandomId(void) const;
	virtual __int64 getUserAuthentication(void);
	virtual __int64 sub_1400CAC50(__int64* a2);
	virtual __int64 registerToUserManager(__int64&, int);
	virtual __int64 resumeWithUserManager(__int64&, int);
	virtual __int64 createUserAuthentication(std::string);
	virtual __int64 createUserAuthentication(unsigned long long, std::string const&);
	virtual __int64 getPlatformId(void) const;
	virtual __int64 getPlatformOnlineId(void) const;

public:
	virtual bool isHoloCursorNeeded(void) const;

private:
	virtual __int64 useController(void) const;
	virtual __int64 useTouchscreen(void) const;

public:
	virtual bool getMouseGrabbed(void) const;

private:
	virtual __int64 currentInputModeIsGamePadOrMotionController(void) const;
	virtual __int64 currentInputModeIsMouseAndKeyboard(void) const;
	virtual __int64 getForceMonoscopic(void) const;
	virtual __int64 allowPicking(void) const;

public:
	virtual bool isShowingMenu(void) const;
	virtual bool isShowingProgressScreen(void) const;
	virtual bool isShowingWorldProgressScreen(void) const;
	virtual bool isShowingDeathScreen(void) const;
	virtual bool isScreenReplaceable(void) const;
	virtual bool isInGame(void) const;
	virtual bool isInRealm(void);

private:
	virtual __int64 readyForShutdown(void) const;

public:
	virtual bool isPrimaryClient(void) const;
	virtual bool isEduMode(void) const;
	virtual bool isGamepadCursorEnabled(void) const;

private:
	virtual void getServerData(void);
	virtual void getServerData(void) const;

public:
	virtual void getLevel(void);
	virtual void getLevel(void) const;
	virtual bool isPreGame(void) const;
	virtual bool isInMultiplayerGame(void) const;
	virtual bool isMultiC_PlayerClient(void) const;
	virtual __int64 sub_14012F590() const;
	virtual __int64 sub_14012F4D0() const;
	virtual __int64 getOptions(void);
	virtual __int64 getOptions(void) const;
	//virtual __int64 getOptionsPtr(void);
	virtual __int64 getUser(void);
	virtual __int64 getUser(void) const;
	virtual __int64 getGameRenderer(void) const;
	virtual __int64 getHolosceneRenderer(void) const;
	virtual __int64 getLevelRenderer(void) const;
	virtual __int64 getLevelRendererCameraProxy(void) const;
public:
	virtual void getCameraManager(void) const;
private:
	virtual __int64 sub_1400CCC08(void) const;

public:
	virtual __int64 getLightTexture(void);

public:
	virtual void setupLevelRendering(__int64&, Actor&);

private:
	virtual __int64 getViewportInfo(void) const;

public:
	virtual void setViewportInfo(__int64 const&);

private:
	virtual __int64 getNormalizedViewportSize(void) const;
	virtual __int64 updateChunkRadius(void);

public:
	virtual void setUITexture(__int64*);

private:
	virtual __int64 getUITexture(void);

public:
	virtual void setLevelTexture(__int64*);

private:
	virtual __int64 getLevelTexture(void);

public:
	virtual void setUICursorTexture(__int64);

	virtual __int64 getUICursorTexture(void) const;
	virtual __int64 getCamera(void);
	virtual __int64 getShaderColor(void);
	virtual __int64 getDarkShaderColor(void);
	virtual __int64 clearGraphicsCache(void);
	virtual __int64 getNormalizedUICursorTransform(__int64&, float);
	virtual __int64 shouldRenderUICursor(void) const;
	virtual bool sub_1400CD3B0(void);
	virtual bool sub_1400CD3B1(void);
	virtual __int64 getGuiScale(void) const;
	virtual __int64 getGuiScaleOption(void) const;
	virtual __int64 getGuiScaleOffset(void) const;

public:
	virtual void setGuiScaleOffset(int);

private:
	virtual __int64 renderEditorGui(__int64&, bool);

public:
	virtual C_GuiData* getGuiData(void);
	virtual C_GuiData* getGuiData(void) const;

public:
	class LocalPlayer* LocalPlayer() {
		if (this != nullptr) {
			return *reinterpret_cast<class LocalPlayer**>(reinterpret_cast<__int64>(this) + 0x138);
		}
		else {
			return nullptr;
		}
	}

	class MinecraftGame* MinecraftGame() {
		if (this != nullptr) {
			return *reinterpret_cast<class MinecraftGame**>(reinterpret_cast<__int64>(this) + 0x98);
		}
		else {
			return nullptr;
		}
	}

	void displayClientMessage(std::string* a2) {
		using displayClientMessage = void(__thiscall*)(void*, TextHolder&);
		static displayClientMessage displayMessageFunc = reinterpret_cast<displayClientMessage>(Utils::FindSig("48 89 5C 24 ?? 55 48 8D 6C 24 ?? 48 81 EC ?? ?? ?? ?? 48 C7 45 4F ?? ?? ?? ?? 33 DB 48 89 5D ?? 88 5D"));

		TextHolder text = TextHolder(*a2);

		if (displayMessageFunc != nullptr)
			displayMessageFunc(this, text);
	}

	bool isValidTarget(class Actor* Entity) {
		if (Entity == nullptr) {
			return false;
		}

		if (Entity->isInvisible() || !Entity->isAlive() || Entity->isImmobile()) {
			return false;
		}

		if (Entity->getEntityTypeId() > 60 && Entity->getEntityTypeId() < 104 && Entity->getEntityTypeId() != 63) {
			return false;
		}

		if (Entity->getFormattedNameTag().length() <= 1) {
			return false;
		}

		if (!(this->LocalPlayer()->canAttack(Entity, false))) {
			return false;
		}

		return true;
	}

	inline GameSettingsInput* getGameSettingsInput() { return this->ptr->ptr->ptr->settingsInput; };
};