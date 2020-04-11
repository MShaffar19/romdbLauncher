#include "config.h"
#include "file.h"
#include "utils.h"

using namespace std::literals;

const std::string defaultConfig{
	R"(# romdb Launcher configuration

# romdb files to load
romdb=
romdb=

# romdb Launcher options
position=100,100
size=640,480
deleteFileOnClose=true
allSystems=true
includeMedia=true
activeSystems=
currentSearch=

# system options
# 
# system - romdb system code to configure
# emulator - full path of emulator
# args - arguments to pass to emulator. full rom path will be appended at the end to load or by replacing %file%
# rompath - path of cache folder to extract roms. this path should be created just for romdb Launcher
# alias - use the same system configuation of the current system
#
system=
emulator=
args=
rompath=
#alias=
)"
};

void Config::load()
{
	// clear line indexes
	linePosition = -1;
	lineSize = -1;
	lineDeleteFileOnClose = -1;
	lineAllSystems = -1;
	lineIncludeMedia = -1;
	lineActiveSystems = -1;
	lineCurrentSearch = -1;

	configLines.clear();
	romdbFiles.clear();
	systems.clear();

	// load from program path
	configPath = file::getProgramPath() / "config.txt";
	if (!std::filesystem::exists(configPath))
	{
		// load from user's profile roaming folder
		auto path = file::getUserRoamingPath() / "romdbLauncher";
		configPath = path / "config.txt";
		if (!std::filesystem::exists(configPath))
		{
			std::filesystem::create_directories(path);
			file::writeText(configPath.wstring(), defaultConfig);
			configLines = utils::splitStringInLines(defaultConfig);
		}
	}

	if (configLines.empty())
		configLines = utils::splitStringInLines(file::readText(configPath.wstring()));

	// remove trailing blank lines
	for (int32_t i = configLines.size() - 1; i >= 0; i--)
	{
		if (configLines[i].empty())
			configLines.pop_back();
		else
			break;
	}

	int currentSystem = -1;
	for (int32_t i = 0; (size_t)i < configLines.size(); i++)
	{
		const auto& line = configLines[i];
		if (utils::startsWith(line, "#"))
		{
			continue;
		}
		else if (utils::startsWith(line, "position="))
		{
			if (linePosition >= 0)
				continue;
			linePosition = i;
			auto str = utils::splitStringIn2(utils::replaceString(line, "position="sv, ""sv), ',');
			positionX = (int)std::strtol(str.first.c_str(), nullptr, 10);
			positionY = (int)std::strtol(str.second.c_str(), nullptr, 10);
		}
		else if (utils::startsWith(line, "size="))
		{
			if (lineSize >= 0)
				continue;
			lineSize = i;
			auto str = utils::splitStringIn2(utils::replaceString(line, "size="sv, ""sv), ',');
			sizeX = (int)std::strtol(str.first.c_str(), nullptr, 10);
			sizeY = (int)std::strtol(str.second.c_str(), nullptr, 10);
		}
		else if (utils::startsWith(line, "deleteFileOnClose="))
		{
			if (lineDeleteFileOnClose >= 0)
				continue;
			lineDeleteFileOnClose = i;
			deleteFileOnClose = utils::startsWith(utils::replaceString(line, "deleteFileOnClose="sv, ""sv), "true");
		}
		else if (utils::startsWith(line, "allSystems="))
		{
			if (lineAllSystems >= 0)
				continue;
			lineAllSystems = i;
			allSystems = utils::startsWith(utils::replaceString(line, "allSystems="sv, ""sv), "true");
		}
		else if (utils::startsWith(line, "includeMedia="))
		{
			if (lineIncludeMedia >= 0)
				continue;
			lineIncludeMedia = i;
			includeMedia = utils::startsWith(utils::replaceString(line, "includeMedia="sv, ""sv), "true");
		}
		else if (utils::startsWith(line, "activeSystems="))
		{
			if (lineActiveSystems >= 0)
				continue;
			lineActiveSystems = i;
		}
		else if (utils::startsWith(line, "currentSearch="))
		{
			if (lineCurrentSearch >= 0)
				continue;
			lineCurrentSearch = i;
			currentSearch = utils::replaceString(line, "currentSearch="sv, ""sv);
		}
		else if (utils::startsWith(line, "romdb="))
		{
			auto romdbFile = utils::replaceString(line, "romdb="sv, ""sv);
			if (romdbFile.empty())
				continue;
			romdbFiles.insert(romdbFile);
		}
		else if (utils::startsWith(line, "system="))
		{
			auto systemCode = utils::replaceString(line, "system="sv, ""sv);
			if (systemCode.empty())
				continue;
			auto systemPtr = getSystem(systemCode);
			if (!systemPtr)
			{
				ConfigSystem system;
				system.index = systems.size();
				system.code = systemCode;
				systems.push_back(system);
				currentSystem = system.index;
			}
		}
		else if (utils::startsWith(line, "emulator="))
		{
			if (currentSystem >= 0)
			{
				systems[currentSystem].emulator = utils::replaceString(line, "emulator="sv, ""sv);
			}
		}
		else if (utils::startsWith(line, "args="))
		{
			if (currentSystem >= 0)
			{
				systems[currentSystem].args = utils::replaceString(line, "args="sv, ""sv);
			}
		}
		else if (utils::startsWith(line, "rompath="))
		{
			if (currentSystem >= 0)
			{
				systems[currentSystem].romPath = utils::replaceString(line, "rompath="sv, ""sv);
			}
		}
		else if (utils::startsWith(line, "alias="))
		{
			if (currentSystem >= 0)
			{
				auto alias = utils::replaceString(line, "alias="sv, ""sv);
				if (alias.empty())
					continue;
				auto systemAlias = systems[currentSystem];
				systemAlias.index = systems.size();
				systemAlias.code = alias;
				systems.push_back(systemAlias);
			}
		}
	}

	// set active systems
	if (lineActiveSystems >= 0)
	{
		auto str = utils::replaceString(configLines[lineActiveSystems], "activeSystems="sv, ""sv);
		while (!str.empty())
		{
			auto strPair = utils::splitStringIn2(str, ',');
			if (!strPair.first.empty())
			{
				auto systemPtr = getSystem(strPair.first);
				if (systemPtr)
					systemPtr->active = true;
			}
			str = strPair.second;
		}
	}
}

void Config::save()
{
	std::string str = "position=" + std::to_string(positionX) + "," + std::to_string(positionY);
	if (linePosition >= 0 && (size_t)linePosition < configLines.size())
		configLines[linePosition] = str;
	else
		configLines.push_back(str);

	str = "size=" + std::to_string(sizeX) + "," + std::to_string(sizeY);
	if (lineSize >= 0 && (size_t)lineSize < configLines.size())
		configLines[lineSize] = str;
	else
		configLines.push_back(str);

	str = "deleteFileOnClose=";
	if (deleteFileOnClose)
		str += "true";
	else
		str += "false";
	if (lineDeleteFileOnClose >= 0 && (size_t)lineDeleteFileOnClose < configLines.size())
		configLines[lineDeleteFileOnClose] = str;
	else
		configLines.push_back(str);

	str = "allSystems=";
	if (allSystems)
		str += "true";
	else
		str += "false";
	if (lineAllSystems >= 0 && (size_t)lineAllSystems < configLines.size())
		configLines[lineAllSystems] = str;
	else
		configLines.push_back(str);

	str = "includeMedia=";
	if (includeMedia)
		str += "true";
	else
		str += "false";
	if (lineIncludeMedia >= 0 && (size_t)lineIncludeMedia < configLines.size())
		configLines[lineIncludeMedia] = str;
	else
		configLines.push_back(str);

	str = "activeSystems=";
	for (const auto& system : systems)
	{
		if (system.active)
			str += system.code + ",";
	}
	if (lineActiveSystems >= 0 && (size_t)lineActiveSystems < configLines.size())
		configLines[lineActiveSystems] = str;
	else
		configLines.push_back(str);

	str = "currentSearch=" + currentSearch;
	if (lineCurrentSearch >= 0 && (size_t)lineCurrentSearch < configLines.size())
		configLines[lineCurrentSearch] = str;
	else
		configLines.push_back(str);

	file::writeText(configPath.wstring(), utils::mergeLines(configLines));
}

bool Config::isSystemActive(const std::string& systemCode)
{
	auto system = getSystem(systemCode);
	if (system)
		return system->active;
	return false;
}

ConfigSystem* Config::getSystem(const std::string& systemCode)
{
	for (auto& system : systems)
	{
		if (system.code == systemCode)
			return &system;
	}
	return {};
}
