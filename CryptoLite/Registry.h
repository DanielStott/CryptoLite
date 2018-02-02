#pragma once
#include "stdafx.h"

class Registry
{
public:
	static void RegisterProgram();
	static void RemoveProgram();
private:
	static BOOL RegisterForStartup(PCWSTR pszAppName, PCWSTR pathToExe);
	static BOOL RemoveFromStartup(PCWSTR pszAppName, PCWSTR pathToExe);
};