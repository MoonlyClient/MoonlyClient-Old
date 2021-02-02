#pragma once

#include <map>
#include <vector>

#include "Utils.h"

class Menu {
public:
	static void init();
	static void DrawAll();
	static void render();
	static void onKeyUpdate(int key, bool isDown);
	static void onMouseClickUpdate(int key, bool isDown);
	static void onLoadConfig(void* confVoid);
	static void onSaveConfig(void* confVoid);
};
