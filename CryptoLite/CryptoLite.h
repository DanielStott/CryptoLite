#pragma once
#include "resource.h"
#include "FileSearch.h"
#include "FileIO.h"
#include "Crypto.h"
#include "HTTP.h"
#include "Registry.h"
#include <Windows.h>
#include <shlobj.h>
#include <vector> 
#include <Aclapi.h>

#define IDC_MAIN_BUTTON	101			// Button identifier
#define IDC_MAIN_EDIT	102			// Edit box identifier
HWND hEdit;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM);
wchar_t docPath[MAX_PATH];
wchar_t tempPath[MAX_PATH];

