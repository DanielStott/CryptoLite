#pragma once
#include <string>
#include <urlmon.h>
#pragma comment(lib, "Urlmon.lib")
#include "FileIO.h"

class HTTP {
public:
	static std::string GetKey(std::wstring &path);
};
