#include "Utils.h"

uint32 GEHashString(const char* str)
{
	return uint32(std::hash<std::string>{}(std::string(str)));
}

uint32 GEHashString(const std::string& str)
{
	return uint32(std::hash<std::string>{}(str));
}

uint32 GEGetScreenWidth() { return 1024; }
uint32 GEGetScreenHeight() { return 768; }