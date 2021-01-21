#include "Utils.h"
#include "../SDK/Minecraft.h"
#include "../SDK/Classes/GameSettingsInput.h"

HMODULE Utils::hModule = nullptr;
bool Utils::running = false;

std::vector<std::string> SortArrayOfStrings(std::vector<std::string> stringVecArr) {
	std::vector<std::string> stringArr;

	for (int I = 0; I < stringVecArr.size(); I++) {
		stringArr.push_back(stringVecArr.at(I));
	};

	for (int I = 0; I < stringArr.size(); I++) {
		std::string temp = stringArr[I];

		int J = I - 1;
		while (J >= 0 && temp.length() < stringArr[J].length()) {
			stringArr[J + 1] = stringArr[J];
			J--;
		}
		stringArr[J + 1] = temp;
	};
	return stringArr;
};

bool Utils::hasExtension(std::string fileName) {
	std::string::size_type idx;
	idx = fileName.rfind('.');

	return idx != std::string::npos;
}

bool Utils::doesPathExist(std::string path) {
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
}

void Utils::CreateDir(std::string path) {
	if (!hasExtension(path)) {
		std::string envPath = getenv("APPDATA");
		if (envPath.length() <= 0)
			return;

		std::string roamingDir = envPath + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\");
		if (!doesPathExist(roamingDir))
			return;

		std::string precisePath = std::string(roamingDir + path);
		std::filesystem::create_directories(precisePath);
	}
}

void Utils::DeletePath(std::string path) {
	std::string precisePath = getenv("APPDATA") + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\" + path);
	if (doesPathExist(precisePath)) {
		if (std::filesystem::is_directory(precisePath)) {
			std::filesystem::remove_all(precisePath);
		}
		else {
			std::filesystem::remove(precisePath);
		}
	}
}

void Utils::WriteToFile(std::string str, std::string path) {
	if (hasExtension(path)) {
		std::string precisePath = getenv("APPDATA") + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\" + path);
		if (!doesPathExist(precisePath)) {
			std::filesystem::path p(precisePath);
			std::filesystem::create_directories(p.parent_path().string());
		}

		CloseHandle(CreateFileA(precisePath.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL));
		if (doesPathExist(precisePath) && str.length() > 0) {
			std::ofstream fileOutput;
			fileOutput.open(precisePath.c_str(), std::ios_base::app);
			fileOutput << str << std::endl;
			fileOutput.close();
		}
	}
}

void Utils::DebugLogOutput(std::string str) {
	WriteToFile(str, "MoonlyClient/Output.txt");
	return;
}

uintptr_t Utils::FindAddr(uintptr_t ptrBase, std::vector<unsigned int> offsets) {
	uintptr_t curr = NULL;
	if (ptrBase != NULL) {
		curr = ptrBase;
		for (unsigned int I = 0; I < offsets.size(); I++) {
			curr = *(uintptr_t*)(curr += offsets[I]);
			if (curr == NULL) {
				break;
			}
		}
	}
	return curr;
}

uintptr_t Utils::FindSig(const char* szSignature) {
	const char* pattern = szSignature;
	uintptr_t firstMatch = 0;
	static const uintptr_t rangeStart = (uintptr_t)GetModuleHandleA("Minecraft.Windows.exe");
	static MODULEINFO miModInfo;
	static bool init = false;
	if (!init) {
		init = true;
		GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	}
	static const uintptr_t rangeEnd = rangeStart + miModInfo.SizeOfImage;

	BYTE patByte = GET_BYTE(pattern);
	const char* oldPat = pattern;

	for (uintptr_t pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pattern)
			return firstMatch;

		while (*(PBYTE)pattern == ' ')
			pattern++;

		if (!*pattern)
			return firstMatch;

		if (oldPat != pattern) {
			oldPat = pattern;
			if (*(PBYTE)pattern != '\?')
				patByte = GET_BYTE(pattern);
		}

		if (*(PBYTE)pattern == '\?' || *(BYTE*)pCur == patByte)
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pattern[2])
				return firstMatch;

			pattern += 2;
		}
		else
		{
			pattern = szSignature;
			firstMatch = 0;
		}
	}
}

std::string Utils::ptrToStr(uintptr_t ptr) {
	std::ostringstream ss;
	ss << std::hex << ((UINT64)ptr) << std::endl;
	return ss.str();
}

std::map<uint64_t, bool> Utils::KeyMapping;

bool Utils::isKeyDown(int key) {
	static uintptr_t keyMapOffset = 0x0;

	if (keyMapOffset == 0x0) {
		uintptr_t sigOffset = FindSig("48 8D 0D ?? ?? ?? ?? 89 1C B9");
		if (sigOffset != 0x0) {
			int offset = *reinterpret_cast<int*>((sigOffset + 3));
			keyMapOffset = sigOffset - Minecraft::ModuleBase() + offset + 7;
			Utils::DebugLogOutput("KeyMap: " + std::to_string(keyMapOffset + Minecraft::ModuleBase()));
		}
	}

	return *reinterpret_cast<bool*>(Minecraft::ModuleBase() + keyMapOffset + ((uintptr_t)key * 0x4));
}

/* Render Utils */

#include "../SDK/Classes/ClientInstance.h"

class MinecraftUIRenderContext* RenderUtils::CachedContext = nullptr;
class BitmapFont* RenderUtils::CachedFont = nullptr;

void RenderUtils::SetContext(class MinecraftUIRenderContext* Context, class BitmapFont* Font) {
	CachedContext = Context;
	CachedFont = Font;
}

void RenderUtils::FlushText() {
	if (CachedContext != nullptr) CachedContext->flushText(0);
}

float RenderUtils::GetTextWidth(std::string text, float textSize) {
	if (CachedContext != nullptr) {
		TextHolder myText(text);
		return CachedContext->getLineLength(CachedFont, &myText, textSize, false);
	}
}

void RenderUtils::RenderText(std::string textStr, Vec2 pos, MC_Colour color, float textSize, float alpha) {
	TextHolder text(textStr);
	static uintptr_t caretMeasureData = 0xFFFFFFFF;

	pos.y -= 1;

	float posF[4];
	posF[0] = pos.x;
	posF[1] = pos.x + 1000;
	posF[2] = pos.y;
	posF[3] = pos.y + 1000;

	TextMeasureData textMeasure{};
	memset(&textMeasure, 0, sizeof(TextMeasureData));
	textMeasure.textSize = textSize;

	CachedContext->drawText(CachedFont, posF, &text, color.arr, alpha, 0, &textMeasure, &caretMeasureData);
};

void RenderUtils::DrawCenteredText(Vec2 pos, std::string text, MC_Colour colour, float size, float textOpacity) {
	pos.x -= RenderUtils::GetTextWidth(text, size) / 2;
	RenderUtils::RenderText(text, pos, colour, size, textOpacity);
}

void RenderUtils::DrawKeystroke(char key, Vec2 pos) {
	std::string keyString = Utils::getKeybindName(key);
	GameSettingsInput* input = Minecraft::ClientInstance()->getGameSettingsInput();

	if (key == *input->spaceBarKey) keyString = "-";

	Vec4 rectPos(pos.x ,pos.y, pos.x + ((key == *input->spaceBarKey) ? 64.f : 20.f), pos.y + 20.f);
	Vec2 textPos((rectPos.x + 3.5 + (rectPos.z - rectPos.x) / 2) - (GetTextWidth(keyString, 1) / 1.f), rectPos.y + 12.f - CachedFont->getLineHeight() / 2.f);

	FillRectangle(rectPos, Utils::isKeyDown(key) ? MC_Colour(255, 255, 255) : MC_Colour(0, 0, 0), .15f);
	RenderText(keyString, textPos, MC_Colour(255, 255, 255), 1.f, 1.f);
}

void RenderUtils::FillRectangle(Vec4 position, MC_Colour colour, float alpha) {
	if (CachedContext != nullptr) {
		CachedContext->fillRectangle(Vec4(position.x, position.z, position.y, position.w), colour, alpha);
	}
}

void RenderUtils::DrawRectangle(Vec4 position, MC_Colour colour, float alpha, float lineWidth) {
	if (CachedContext != nullptr) {
		lineWidth /= 2;
		FillRectangle(Vec4(position.x - lineWidth, position.y - lineWidth, position.z + lineWidth, position.y + lineWidth), colour, alpha);
		FillRectangle(Vec4(position.x - lineWidth, position.y, position.x + lineWidth, position.w), colour, alpha);
		FillRectangle(Vec4(position.z - lineWidth, position.y, position.z + lineWidth, position.w), colour, alpha);
		FillRectangle(Vec4(position.x - lineWidth, position.w - lineWidth, position.z + lineWidth, position.w + lineWidth), colour, alpha);
	}
}