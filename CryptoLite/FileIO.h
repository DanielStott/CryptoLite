#pragma once
#include "stdafx.h"
#include <Windows.h>
#include <vector> 
#include <iostream>
#include <vector> 
#include <string>
class FileIO {

public:
	static std::vector<std::string> readFile(std::wstring &path);
	static void saveFile(std::wstring & path, std::string & data);
	static void saveFile(std::wstring &path, std::vector<std::string> &data);
	static void removeFile(std::wstring &path);
	static void coutFile(std::wstring &path);
	static bool fileExists(std::wstring & path);
private:
	


};