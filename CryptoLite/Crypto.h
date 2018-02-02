#pragma once
#include <Windows.h>
#include <vector> 
#include <iostream>
#include <vector> 
#include <string>
#include <algorithm>

class Crypto {

public:
	Crypto(std::string setKey);
	void encrypt(std::string & data);
	void decrypt(std::string & data);
	void encrypt(std::vector<std::string> &data);
	void decrypt(std::vector<std::string> &data);
	bool checkKey(std::string & data);
	~Crypto();
	
private:
	void ceaserShift(std::string &lineToShift, int shift);
	void subCipherEncrypt(std::string &line);
	void subCipherDecrypt(std::string &line);
	void vigenereCipher(std::string &input, bool encipher);
	void vigenereEncrypt(std::string &input);
	void vigenereDecrypt(std::string &input);
	std::string key;
};