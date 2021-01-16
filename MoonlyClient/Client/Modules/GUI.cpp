#include "../ClientManager.h"
#include "../../Other/Utils.h"
#include "GUI.h"

void GUI::onRender() {
	RenderUtils::RenderText("Moonly Client", Vec2(5, 5), MC_Colour(255, 255, 255, 255), 1.0f, 1.0f);
}