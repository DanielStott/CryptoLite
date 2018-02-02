#include "stdafx.h"
#include "FileSearch.h"

//Checks to see if the directory path exists
bool FileSearch::dirExists(const LPCTSTR dirPath)
{
	DWORD ftyp = GetFileAttributes(dirPath);
	if (ftyp == INVALID_FILE_ATTRIBUTES) return false;  //Broken Path

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY) return true;   // Is directory

	return false;    // Not a directory
}

//Loops all files in given path looking for given extension
void  FileSearch::searchDir(std::vector<std::wstring> &fileLocations, std::wstring path, wchar_t *extension)
{
	//Checks if path exists
	if (dirExists(path.c_str()))
	{
		//Adds \\* to the end of the path
		std::wstring dirPath = path + L"\\*";


		WIN32_FIND_DATA file;
		//Creates a search handle
		HANDLE search_handle = FindFirstFile(dirPath.c_str(), &file);
		//Makes sure file is valid
		if (search_handle != INVALID_HANDLE_VALUE)
		{
			//Loops through all files in directory
			do
			{		
				std::wstring fullPath = path + L"\\" + file.cFileName;
				//Folders that end in . are ignored (Stops the infinite file search loop)
				if (((std::wstring)file.cFileName).back() != '.')
				{
					//Checks to see if it is a file or folder
					if (dirExists(fullPath.c_str()))
					{
						searchDir(fileLocations, fullPath, extension);
						//std::wcout << "Directory found: " << file.cFileName << std::endl;

					}
					//checks if the filename contains .txt			
					else if (wcsstr(file.cFileName, extension))
					{
						fileLocations.push_back(fullPath);
						std::wcout << "Text file found: " << fullPath << std::endl;
					}
				}
				//Goes to next file/folder
			} while (FindNextFileW(search_handle, &file));
			FindClose(search_handle);
			return;
		}
		else
			std::wcout << "Error: " << path << "\n";
	}
}

