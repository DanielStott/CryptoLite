#include "stdafx.h"
#include "FileIO.h"
#include <iostream>
#include <iterator>
#include <fstream>

//Reads file from given path
std::vector<std::string> FileIO::readFile(std::wstring &path)
{
	std::vector<std::string> data;
	std::string line;
	std::ifstream file(path);
	//Checks to make sure file is open
	if (file.is_open())
	{
		//Reads each line
		while (getline(file, line))
		{
			data.push_back(line);
		}
		file.close();
		return data;
	}	
}

//Saves data to path location
void FileIO::saveFile(std::wstring &path, std::string &data)
{
	std::ofstream file(path);

	if (file)
	{
			file << data << std::endl;
	}
}

//Saves data to path location
void FileIO::saveFile(std::wstring &path, std::vector<std::string> &data)
{
	std::ofstream file(path);

	if (file)
	{
		//Loops through every vector entry and writes the line to the file
		for (std::string &s : data)
		{
			file << s << std::endl;
		};
	}
}

//Deletes the file at given path
void FileIO::removeFile(std::wstring &path)
{
	DeleteFile(path.c_str());
}

//Used to debug. Writes file content to console
void FileIO::coutFile(std::wstring &path)
{
	std::wstring line;
	std::wifstream file(path);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			std::wcout << line << std::endl;
		}
		file.close();
	}
}

//Checks to make sure file exists
bool FileIO::fileExists(std::wstring &path)
{
	std::wifstream file(path);
	return file.good();
}