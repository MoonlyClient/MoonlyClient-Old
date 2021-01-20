#pragma once

#include <map>
#include <vector>

#include "Utils.h"

struct ClickModule {
	bool isExtended = false;
};

struct ClickWindow {
	ClickWindow() {
		pos.x = 0;
		pos.y = 0;

		size.x = 30;
		size.y = 30;
	}

	Vec2 pos;
	Vec2 size;
	bool isExtended = true;
	bool isInAnimation = false;
	float animation = 0;
	const char* name;
	std::map<unsigned int, std::shared_ptr<ClickModule>> moduleMap;

	int yOffset = 0;
};

class Menu {
private:

	inline static std::shared_ptr<ClickWindow> getWindow(const char* id);
	inline static std::shared_ptr<ClickModule> getClickModule(std::shared_ptr<ClickWindow> window, const char* id);

public:
	static void init();
	static void render();
	static void onKeyUpdate(int key, bool isDown);
	static void onMouseClickUpdate(int key, bool isDown);
	static void onLoadConfig(void* confVoid);
	static void onSaveConfig(void* confVoid);
};
