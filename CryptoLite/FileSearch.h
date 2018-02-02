#pragma once
#include "stdafx.h"
#include <Windows.h>
#include <vector> 
#include <iostream>
#include <vector> 
#include <string>
class FileSearch {

public:
	static void searchDir(std::vector<std::wstring>& fileLocations, std::wstring path, wchar_t *extension);

private:
	static bool dirExists(LPCTSTR);

};