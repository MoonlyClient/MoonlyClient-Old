#pragma once

#include "TextHolder.h"
#include "MinecraftUIRenderContext.h"
#include "Actor.h"
#include "LocalPlayer.h"
#include "GameMode.h"
#include "GuiData.h"
#include "GameSettingsInput.h"
#include "LoopbackPacketSender.h"

class C_Player;

class C_Minecraft {
public:
	char pad_0x0000[0xB0];  //0x0000

	float* timer;  //0x00B0
};

class BlockTessellator;

class ResourceLocation {
public:
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
	public:
		__int64* clientTexture;
		char pad[0x8];
		ResourceLocation resourceLocation; // 0x10

	
		__int64* getClientTexture() {
			return this->clientTexture;
		}
	};
	class MaterialPtr {
	public:
		std::shared_ptr<void> materialPtr;

	
		MaterialPtr(const std::string& materialName);
	};
};


class LevelRenderer {
public:
	char pad_0x0000[0x58];  //0x0000

	mce::TextureGroup* textureGroup; // 0x0058

	char pad_0x0060[0xE0];  //0x0060

	mce::TexturePtr atlasTexture; // 0x140

	char pad_0x0188[0x150];  //0x0188

	BlockTessellator* blockTessellator; // 0x02D8

	char pad_0x02F0[0x5EC];  //0x02E0

	Vec3 origin;  //0x0890

	__int64 getLevelRendererPlayer() {
		return reinterpret_cast<__int64>(this) + 0x310;
	}
};

struct FontEntry {
public:
	BitmapFont* font;

private:
	void* sharedFontPtr;
};

struct FontList {
public:
	FontEntry fontEntries[9];
};

struct FontRepository {
private:
	uintptr_t* font_repository_vtable;  // 0x0000
	__int64 pad;                        // 0x0008
	void* ptrToSelf;                    // 0x0010
	void* ptrToSelfSharedPtr;           // 0x0018
	__int64 pad2;                       // 0x0020
public:
	FontList* fontList;   //0x0028
};

class MinecraftGame {
public:
	FontRepository* getFontRepository() {
		return *reinterpret_cast<FontRepository**>(reinterpret_cast<__int64>(this) + 0x100);
	}

	BitmapFont* getWtfFont() {
		return this->getFontRepository()->fontList->fontEntries[0].font;
	};

	BitmapFont* getCleanFont() {
		return this->getFontRepository()->fontList->fontEntries[7].font;
	};

	BitmapFont* getStrongFont() {
		return this->getFontRepository()->fontList->fontEntries[6].font;
	}

	BitmapFont* getMinecraftiaFont() {
		return this->getFontRepository()->fontList->fontEntries[3].font;
	}

	bool canUseKeys() {
		return *(bool*)(reinterpret_cast<uintptr_t>(this) + 0x2F8);
	}
};

struct PtrToGameSettings3 {

	char pad_0x0000[0x18];

	GameSettingsInput* settingsInput;
};

struct PtrToGameSettings2 {

	char pad_0x0000[0x148];

	PtrToGameSettings3* ptr;
};

struct PtrToGameSettings1 {

	char pad_0x0000[0x18];

	PtrToGameSettings2* ptr;
};

class ClientInstance {
public:
	char firstPad[0x90];  //0x0008

	MinecraftGame* minecraftGame;  //0x0098

	MinecraftGame* N0000080C;  //0x00A0

	MinecraftGame* N0000080D;  //0x00A8

	C_Minecraft* minecraft;  //0x00B0

	char pad_0x0068[0x8];  //0x00B8

	LevelRenderer* levelRenderer;  //0x00C0

	char pad_0x0078[0x8];  //0x00C8

	LoopbackPacketSender* loopbackPacketSender;  //0x00D0

	char pad_0x0088[0x18];  //0x00D8

	PtrToGameSettings1* ptr;  //0x00F0

	virtual __int64 destructorClientInstance();
	virtual void destructorClientInstance2();

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


	virtual bool isLeaveGameDone(void) const;
	virtual void setupPlayScreenForLeaveGame(void);


	virtual __int64 resetPrimaryClient(void);
	virtual __int64 resetGameSession(void);
	virtual __int64 tick(void);
	virtual __int64 frameUpdate(__int64&);
	virtual __int64 update(bool);
	virtual __int64 endFrame(void);
	virtual __int64 startSubClientLateJoin(bool);


	virtual void setupClientGame(__int64&&, bool);


	virtual __int64 getRegion(void) const;
	virtual __int64 getLocalC_Player(void);
	virtual __int64 getLocalC_Player(void) const;
	virtual __int64 getCameraEntity(void) const;


	virtual void setCameraEntity(__int64*);


	virtual __int64 getCameraTargetEntity(void) const;


	virtual void setCameraTargetEntity(__int64*);
	virtual bool isLeavingGame(void) const;
	virtual bool isDestroyingGame(void) const;


	virtual __int64 isShuttingDown(void) const;
	virtual __int64 useLowFrequencyUIRender(void) const;


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


	virtual __int64 getHoloviewerScale(void) const;
	virtual __int64 getSplitScreenCount(void) const;


	virtual bool isStereoRendering(void) const;
	virtual bool isPlatformNX(void) const;
	virtual bool isLocalSplitscreenWith(__int64 const&) const;
	virtual bool isValidCrossPlatformSkin(void) const;
	virtual __int64 isSelectedSkinInitialized(void);


	virtual __int64 getSplitScreenInfo(void) const;
	virtual __int64 getCurrentMaxGUIScaleIndex(void) const;
	virtual __int64 getRealityModeFrameFactor(void) const;


	virtual void setRealityModeFrameFactor(float const&);


	virtual __int64 getRealityModeToggleTriggered(void) const;


	virtual void setRealityModeToggleTriggered(bool);


	virtual bool getHandlingControllerDisconnect(void);


	virtual void setOpenControllerDisconnectScreen(bool);


	virtual __int64 getClientPlayMode(void) const;


	virtual void setClientPlayMode(__int64 const&);


	virtual __int64 getLivingRoomForCredits(void) const;


	virtual void setLivingRoomForCredits(bool);


	virtual __int64 getCreditsCallback(void);


	virtual void setCreditsCallback(__int64);
	virtual void setupTransitionForCredits(__int64);


	virtual __int64 refreshScreenSizeData(void);
	virtual __int64 onScreenSizeChanged(int, int, float);
	virtual __int64 onGuiScaleOffsetChanged(void);
	virtual __int64 onSafeZoneChanged(void);
	virtual __int64 quit(std::string const&, std::string const&);


	virtual __int64 getMinecraftGame(void) const;


	virtual __int64 getAutomationClient(void) const;
	virtual __int64 getScreenshotStreamer(void) const;
	virtual __int64 getEventing(void) const;
	virtual __int64 unknown(__int64 a1);
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
	virtual __int64 getPersonaPieceCollectionModel(void) const;
	virtual __int64 getPersonaRepository(void) const;
	virtual __int64 getTextures(void) const;
	virtual __int64 getStoreCacheTextures(void) const;
	virtual __int64 getMinecraftGraphics(void) const;
	virtual __int64 getUIRepository(void) const;
	virtual __int64 getUserManager(void) const;
	virtual __int64 wantToQuit(void) const;


	virtual bool isPrimaryLevelCrossPlatformMultiplayer(void) const;
	virtual bool isPrimaryLevelMultiplayer(void) const;
	virtual bool isAdhocEnabled(void) const;


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
	virtual char tryStartDayOneExperience(void) const;


	virtual bool isReadyToRender(void) const;


	virtual __int64 onDimensionChanged(void);
	virtual __int64 onGameEventNotification(__int64);


	virtual TextHolder getTopScreenName(void) const;
	virtual void setLeaveGameInProgressAsReadyToContinue(void);


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


	virtual bool isHoloCursorNeeded(void) const;


	virtual __int64 useController(void) const;
	virtual __int64 useTouchscreen(void) const;


	virtual bool getMouseGrabbed(void) const;


	virtual __int64 currentInputModeIsGamePadOrMotionController(void) const;
	virtual __int64 currentInputModeIsMouseAndKeyboard(void) const;
	virtual __int64 getForceMonoscopic(void) const;
	virtual __int64 allowPicking(void) const;


	virtual bool isShowingMenu(void) const;
	virtual bool isShowingProgressScreen(void) const;
	virtual bool isShowingWorldProgressScreen(void) const;
	virtual bool isShowingDeathScreen(void) const;
	virtual bool isScreenReplaceable(void) const;
	virtual bool isInGame(void) const;
	virtual bool isInRealm(void);


	virtual __int64 readyForShutdown(void) const;


	virtual bool isPrimaryClient(void) const;
	virtual bool isEduMode(void) const;
	virtual bool isGamepadCursorEnabled(void) const;


	virtual C_Minecraft* getServerData(void);
	virtual C_Minecraft* getServerData(void) const;


	virtual __int64 getLevel(void);
	virtual __int64 getLevel(void) const;
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

	virtual __int64 getCameraManager(void) const;

	virtual __int64 sub_1400CCC08(void) const;


	virtual __int64 getLightTexture(void);


	virtual void setupLevelRendering(__int64&, __int64&);


	virtual __int64 getViewportInfo(void) const;


	virtual void setViewportInfo(__int64 const&);


	virtual __int64 getNormalizedViewportSize(void) const;
	virtual __int64 updateChunkRadius(void);


	virtual void setUITexture(__int64*);


	virtual __int64 getUITexture(void);


	virtual void setLevelTexture(__int64*);


	virtual __int64 getLevelTexture(void);


	virtual void setUICursorTexture(__int64);

	virtual __int64 getUICursorTexture(void) const;
	virtual __int64 getCamera(void);
	virtual __int64 getShaderColor(void);
	virtual __int64 getDarkShaderColor(void);
	virtual __int64 clearGraphicsCache(void);
	virtual __int64 getNormalizedUICursorTransform(__int64&, float);
	virtual __int64 shouldRenderUICursor(void) const;
	virtual __int64 getRenderPlayerModel(void);
	virtual __int64 getCameraFacesPlayerFront(void);
	virtual __int64 getGuiScale(void) const;
	virtual __int64 getGuiScaleOption(void) const;
	virtual __int64 getGuiScaleOffset(void) const;


	virtual void setGuiScaleOffset(int);


	virtual __int64 renderEditorGui(__int64&, bool);


	virtual C_GuiData* getGuiData1(void);
	virtual C_GuiData* getGuiData2(void) const;


	virtual __int64 getGuidedFlowManager(void);
	virtual __int64 getDpadScale(void) const;
	virtual __int64 getDateManager(void) const;
	virtual __int64 addOverrideHoursToDateTime(unsigned int);
	virtual __int64 getToastManager(void);
	virtual __int64 getTopScene(void);
	virtual __int64 getTopScene(void) const;
	virtual __int64 getActiveScene(void);
	virtual __int64 getActiveScene(void) const;
	virtual __int64 getSceneFactory(void) const;
	virtual __int64 getClientSceneStack(void) const;
	virtual __int64 getClientSceneStack(void);
	virtual __int64 sub_140634B30(void) const;
	virtual __int64 getMainSceneStack(void);
	virtual __int64 getMainSceneStack(void) const;
	virtual __int64 getCurrentSceneStack(void) const;
	virtual __int64 getCurrentSceneStack(void);
	virtual __int64 getCurrentUIRouter(void);
	virtual __int64 getCurrentUIRouter(void) const;
	virtual __int64 sub_14012BAB0(void) const;
	virtual __int64 prepareSceneFor(__int64);
	virtual __int64 getCachedScenes(void);


	virtual TextHolder getScreenName(void) const;


	virtual __int64 getScreenTelemetry(void) const;
	virtual __int64 getTopSceneType(void) const;
	virtual __int64 getMobEffectsLayout(void);
	virtual __int64 emoticonifyText(__int64 a2, __int64 a3, char a4);
	virtual __int64 newFunc3(__int64 a2, __int64 a3);
	virtual __int64 onMobEffectsChange(void);


	virtual void setUISizeAndScale(int, int, float);


	virtual __int64 forEachVisibleScreen(__int64, bool);
	virtual __int64 forEachScreen(__int64, bool);
	virtual __int64 forEachScreenConst(__int64, bool) const;
	virtual __int64 updateSceneStack(void);
	virtual __int64 forEachAlwaysAcceptInputScreen(__int64);
	virtual __int64 forEachAlwaysAcceptInputScreenWithTop(__int64);
	virtual __int64 showC_PlayerProfile(std::string const&, __int64);
	virtual __int64 getCurrentInputMode(void) const;


	virtual bool isTouchGameplayAllowed(void) const;


	virtual __int64 getMinecraftInput(void) const;


	virtual void setHoloInput(__int64);


	virtual __int64 getHoloInput(void) const;
	virtual __int64 getVoiceSystem(void) const;
	virtual __int64 getKeyboardManager(void);


	virtual void setVoiceSystem(__int64);
	virtual void setLastPointerLocation(float, float, float);


	virtual __int64 getLastPointerLocation(void);
	virtual __int64 shouldUseLastPointerLocationOnFocusChange(void);
	virtual __int64 adjustGazeCursorByMouse(float, float);
	virtual __int64 currentScreenShouldStealMouse(void);
	virtual __int64 getInProgressBAI(void) const;
	virtual __int64 newDictationDataAvailable(void) const;
	virtual __int64 clearDictationDataAvailable(void);
	virtual __int64 getDictationText(void) const;
	virtual __int64 getPacketSender(void);
	virtual __int64 getClientNetworkSystem(void);
	virtual __int64 getClientNetworkSystem(void) const;


	virtual void setMoveTurnInput(__int64);
	virtual __int64 getMoveTurnInput(void);


	virtual void setupPersistentControls(__int64);


	virtual __int64 resetC_PlayerMovement(void);
	virtual __int64 onClientInputInitComplete(void);


	virtual void setClientInputHandler(__int64);


	virtual __int64 getInput(void) const;
	virtual __int64 getControllerId(void) const;


	virtual bool hasConnectedController(void) const;


	virtual __int64 getClientSubId(void) const;


	virtual void setSuspendInput(bool);
	virtual void setDisableInput(bool);

	virtual void grabMouse(void);
	virtual void releaseMouse(void);
	virtual void refocusMouse(void);


	virtual __int64 resetBai(int);
	virtual __int64 clearInProgressBAI(void);
	virtual __int64 tickBuildAction(void);
	virtual __int64 getSoundEngine(void) const;
	virtual __int64 play(std::string const&, Vec3 const&, float, float);
	virtual __int64 playUI(std::string const&, float, float);
	virtual __int64 muteAudio(void);
	virtual __int64 unMuteAudio(void);
	virtual __int64 fadeOutMusic(void) const;
	virtual __int64 getTaskGroup(void);
	virtual __int64 onFullVanillaPackOnStack(void);


	virtual bool isFullVanillaPackOnStack(void) const;


	virtual __int64 onPlayerLoaded(C_Player&);


	virtual void setClientGameMode(__int64);


	virtual __int64 resetToDefaultGameMode(void);
	virtual __int64 connectToThirdParyServer(std::string const&, std::string const&, int);
	virtual __int64 startExternalNetworkWorld(__int64, std::string const&, bool);
	virtual __int64 checkForPiracy(void);
	virtual __int64 updateChatFilterStatus(void);
	virtual void sub_1400D2A20(void);


	virtual void setBehaviorCommandCallback(__int64);
	virtual void setBehaviorCommandStatus(std::string, __int64);


	virtual __int64 requestScreenshot(__int64&);
	virtual void sub_1400BE0A0(char a2);
	virtual __int64 getDevConsoleLogger(void) const;
	virtual __int64 requestImageFromUrl(std::string const&, __int64);
	virtual __int64 initializeRenderResources(void);
	virtual __int64 postInitRenderResources(void);
	virtual __int64 onAppSuspended(void);
	virtual __int64 onActiveResourcePacksChanged(__int64 const&);
	virtual __int64 reloadEntityRenderers(__int64 const&);
	virtual __int64 getBlockTessellator(void);
	virtual __int64 getBlockEntityRenderDispatcher(void);
	virtual __int64 getEntityRenderDispatcher(void);
	virtual __int64 getEntityBlockRenderer(void);
	virtual __int64 getItemInHandRenderer(void);
	virtual __int64 getItemRenderer(void);
	virtual __int64 getSentMessageHistory(void);
	virtual __int64 getUIProfanityContext(void) const;
	virtual __int64 initTTSClient(__int64&);
	virtual __int64 getTTSClient(void);
	virtual __int64 getTTSClient(void) const;
	virtual __int64 getTTSEventManager(void);
	virtual __int64 addTTSMessage(std::string const&, __int64, bool, bool, bool);
	virtual __int64 initCommands(void);
	virtual __int64 getUserId(void) const;
	virtual __int64 getServerConnectionTime(void) const;
	virtual __int64 getHMDState(void);
	virtual __int64 getHMDState(void) const;


	virtual void setServerPingTime(unsigned int);


	virtual unsigned int getServerPingTime(void) const;


	virtual void setDefaultPlayscreenTab(__int64);
	virtual void setClientInstanceState(__int64 const&);
	virtual void setUIEventCoordinator(__int64&&);


	virtual __int64 getUIEventCoordinator(void);
	virtual __int64 getEventCoordinator(void);
	virtual __int64 computeScreenCoordsFromScreenNormCoords(float, float, short&, short&);
	virtual __int64 getNoBlockBreakUntil(void);


	virtual void setNoBlockBreakUntil(__int64);
	virtual void setDictation(std::string const&);
	virtual void setNewDictationString(bool);
	virtual void setGameModule(__int64);


	virtual __int64 getGameModule(void);
	virtual __int64 getGameCallbacks(void);
	virtual __int64 getStorageAreaStateListener(void);
	virtual __int64 getScriptEngine(void);
	virtual __int64 sendClientEnteredLevel(void);
	virtual __int64 getHitDetectSystem(void);


	virtual bool isPlaying(void) const;


	virtual __int64 getLatencyGraphDisplay(void) const;
	virtual __int64 createSkin(void);
	virtual __int64 onExtendDiskSpace(bool, __int64&, unsigned long long const&, __int64);
	virtual __int64 onLowDiskSpace(bool);
	virtual __int64 onOutOfDiskSpace(bool);
	virtual __int64 onCriticalDiskError(bool, __int64 const&);
	virtual __int64 onLevelCorrupt(void);
	virtual __int64 onGameModeChanged(void);
	virtual __int64 onTick(int, int);
	virtual __int64 onInternetUpdate(void);
	virtual __int64 onGameSessionReset(void);
	virtual __int64 onLevelExit(void);
	virtual __int64 updateScreens(void);

	class LocalPlayer* LocalPlayer() {
		if (this != nullptr) {
			return *reinterpret_cast<class LocalPlayer**>(reinterpret_cast<__int64>(this) + 0x138);
		}
		else {
			return nullptr;
		}
	}

	class C_GuiData* getGuiData() {
		return *reinterpret_cast<class C_GuiData**>((uintptr_t)(this) + 0x4D8);
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

	Vec2* getMousePos() {
		uintptr_t _this = reinterpret_cast<uintptr_t>(this);
		return reinterpret_cast<Vec2*>(_this + 0x448);
	}

	inline GameSettingsInput* getGameSettingsInput() { return this->ptr->ptr->ptr->settingsInput; };
};
