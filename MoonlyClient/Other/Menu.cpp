#include "Menu.h"
#include "Utils.h"
#include "../SDK/Minecraft.h"
#include "../Client/ClientManager.h"

#include <Windows.h>
#include "Module.h"

bool isLeftClickDown = false;
bool isRightClickDown = false;
bool shouldToggleLeftClick = false;
bool shouldToggleRightClick = false;
bool resetStartPos = true;
bool initialised = false;

struct SavedWindowSettings {
	Vec2 pos = { -1, -1 };
	bool isExtended = true;
	const char* name = "";
};

std::map<unsigned int, std::shared_ptr<ClickWindow>> windowMap;
std::map<unsigned int, SavedWindowSettings> savedWindowSettings;

bool isDragging = false;
unsigned int draggedWindow = -1;
Vec2 dragStart = Vec2();

unsigned int focusedElement = -1;
bool isFocused = false;

static constexpr float textPadding = 1.0f;
static constexpr float textSize = 1.0f;
static constexpr float textHeight = textSize * 10.0f;
static constexpr float categoryMargin = 0.5f;
static constexpr float paddingRight = 13.5f;
static constexpr float crossSize = textHeight / 2.f;
static constexpr float crossWidth = 0.3f;
static constexpr float backgroundAlpha = 1;
static const MC_Colour selectedModuleColor = MC_Colour(28, 107, 201);
static const MC_Colour moduleColor = MC_Colour(13, 29, 48);

float currentYOffset = 0;
float currentXOffset = 0;

int timesRendered = 0;

std::shared_ptr<ClickWindow> Menu::getWindow(const char* name) {
	unsigned int id = Utils::getCrcHash(name);

	auto search = windowMap.find(id);
	if (search != windowMap.end()) {  // Window exists already
		return search->second;
	}
	else {
		std::shared_ptr<ClickWindow> newWindow = std::make_shared<ClickWindow>();
		newWindow->name = name;

		auto savedSearch = savedWindowSettings.find(id);
		if (savedSearch != savedWindowSettings.end()) { // Use values from config
			newWindow->isExtended = savedSearch->second.isExtended;
			if (savedSearch->second.pos.x > 0)
				newWindow->pos = savedSearch->second.pos;
		}

		windowMap.insert(std::make_pair(id, newWindow));
		return newWindow;
	}
}

std::shared_ptr<ClickModule> Menu::getClickModule(std::shared_ptr<ClickWindow> window, const char* name) {
	unsigned int id = Utils::getCrcHash(name);

	auto search = window->moduleMap.find(id);
	if (search != window->moduleMap.end()) {  // Window exists already
		return search->second;
	}
	else {  // Create window
	 // TODO: restore settings for position etc
		std::shared_ptr<ClickModule> newModule = std::make_shared<ClickModule>();

		window->moduleMap.insert(std::make_pair(id, newModule));
		return newModule;
	}
}

void Menu::render() {
	if (timesRendered < 10)
		timesRendered++;

	{
		RenderUtils::FillRectangle(Vec4(
			0,
			0,
			Minecraft::ClientInstance()->getGuiData()->widthGame,
			Minecraft::ClientInstance()->getGuiData()->heightGame),
			MC_Colour(33, 34, 48), 0.2f);
	}

	shouldToggleLeftClick = false;
	shouldToggleRightClick = false;
	resetStartPos = false;

	RenderUtils::FlushText();
}

void Menu::init() { initialised = true; }

void Menu::onMouseClickUpdate(int key, bool isDown) {
	switch (key) {
	case 0:  // Left Click
		isLeftClickDown = isDown;
		shouldToggleLeftClick = isDown;
		break;
	case 1:  // Right Click
		isRightClickDown = isDown;
		shouldToggleRightClick = isDown;
		break;
	}
}

void Menu::onKeyUpdate(int key, bool isDown) {
	if (!initialised)
		return;

	Module* menu = ClientManager::GetModuleByName("Menu");

	if (menu == nullptr) {
		return;
	}

	if (!isDown)
		return;

	if (!menu->isEnabled) {
		timesRendered = 0;
		return;
	}

	if (timesRendered < 10)
		return;
	timesRendered = 0;

	switch (key) {
	case VK_ESCAPE:
		menu->isEnabled = false;
		return;
	default:
		if (key == menu->key)
			menu->isEnabled = false;
	}

}

void Menu::onLoadConfig(void* confVoid) {
	// ToDo
}

void Menu::onSaveConfig(void* confVoid) {
	// ToDo
}
