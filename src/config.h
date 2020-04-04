#pragma once

#include <cstdint>
#include <filesystem>
#include "utils.h"

struct ConfigSystem
{
	size_t index = 0;
	std::string code;
	std::string emulator;
	std::string args;
	std::string romPath;
	bool active = false;
	bool available = false;
};

struct Config
{
private:
	// line indexes
	int32_t linePosition = -1;
	int32_t lineSize = -1;
	int32_t lineDeleteFileOnClose = -1;
	int32_t lineAllSystems = -1;
	int32_t lineIncludeMedia = -1;
	int32_t lineActiveSystems = -1;
	int32_t lineCurrentSearch = -1;

public:
	std::filesystem::path configPath;
	std::vector<std::string> configLines;
	std::set<std::string> romdbFiles;
	std::vector<ConfigSystem> systems;

	int32_t positionX = 0x80000000; // CW_USEDEFAULT
	int32_t positionY = 0;
	int32_t sizeX = 640;
	int32_t sizeY = 480;
	bool deleteFileOnClose = true;
	bool allSystems = true;
	bool includeMedia = true;
	std::string currentSearch;

	void load();
	void save();

	bool isSystemActive(const std::string& systemCode);
	ConfigSystem* getSystem(const std::string& systemCode);
};
