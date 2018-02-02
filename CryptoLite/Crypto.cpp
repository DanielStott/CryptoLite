#include "stdafx.h"
#include "Crypto.h"


 std::string key;

 Crypto::Crypto(std::string setKey)
 {
	 //Adds every possible charactar to key
	 key = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" + setKey;
 }

 Crypto::~Crypto()
 {
	 //Deletes the key from memory on deconstruction
	 //delete(&key);
 }

 //Encrypts string
 void Crypto::encrypt(std::string &data)
 {
		 int shiftBy = data.length();
		 //Ceaser Shifts by the length of the line unless it's larger than 26. Halves it until it is smaller than 26 (Every line has a different shift amount)
		 while (shiftBy > 26) shiftBy /= 2;
		 subCipherEncrypt(data);
		 vigenereEncrypt(data);
		 ceaserShift(data, shiftBy);
 }

 //decrypts string
 void Crypto::decrypt(std::string &data)
 {
		 int shiftBy = data.length();
		 //Ceaser Shifts by the length of the line unless it's larger than 26. Halves it until it is smaller than 26 (Most lines are different lengths shift amount)
		 while (shiftBy > 26) shiftBy /= 2;
		 ceaserShift(data, 26 - shiftBy);
		 vigenereDecrypt(data);
		 subCipherDecrypt(data);
 }

 //loops through vector and encryptes each line
 void Crypto::encrypt(std::vector<std::string> &data)
{
	for (std::string &line : data)
	{
		encrypt(line);
	}
}

 //loops through vector and decrypts each line
void Crypto::decrypt(std::vector<std::string> &data)
{
	for (std::string &line : data)
	{
		decrypt(line);
	}
}

//Checks to see if the key is correct (Using is.encrypted file in appdata)
bool Crypto::checkKey(std::string &data)
{
	decrypt(data);
	if (data == "SuccessfullyDecrypted")
	{
		return true;
	}
	return false;
}

//Modified version of: https://www.programmingalgorithms.com/algorithm/caesar-cipher?lang=C%2B%2B
void Crypto::ceaserShift(std::string &line, int shift)
{
	for (char &ch : line)
	{
		if (isalpha((unsigned char)ch))
		{
			char offset = isupper(ch) ? 'A' : 'a';
			ch = (char)((((ch + shift) - offset) % 26) + offset);
		}
	}
}


//Modified version of: https://rosettacode.org/wiki/Substitution_Cipher#C.2B.2B
void Crypto::subCipherEncrypt(std::string &line) {
	std::string encryptedData;
	size_t idx, len = key.length() >> 1;
	for (std::string::iterator i = line.begin(); i != line.end(); i++) {
		idx = key.find_first_of(*i);
		if (idx < len) encryptedData.append(1, key.at(idx + len));
		else encryptedData.append(1, *i);
	}
	line = encryptedData;
}

void Crypto::subCipherDecrypt(std::string &line) {
	std::string encryptedData;
	size_t idx, l = key.length(), len = l >> 1;
	for (std::string::iterator i = line.begin(); i != line.end(); i++) {
		idx = key.find_last_of(*i);
		if (idx >= len && idx < l) encryptedData.append(1, key.at(idx - len));
		else encryptedData.append(1, *i);
	}
	line = encryptedData;
}



//Modified version of: https://www.programmingalgorithms.com/algorithm/vigenere-cipher?lang=C%2B%2B
void Crypto::vigenereCipher(std::string &line, bool encipher)
{
	try
	{


		//Creating clone of the original so we dont overwrite it
		std::string newKey = key;
		//Removes none alpha characters from the key
		for (size_t i = 0; i < newKey.size(); ++i)
		{
			if (!isalpha((unsigned char)newKey[i]))
				newKey.erase(i, 1);
		}
		int keyLen = newKey.size();

		std::string output = "";
		int nonAlphaCharCount = 0;

		for (size_t i = 0; i < line.size(); i++)
		{
			if (isalpha((unsigned char)line[i]))
			{
				bool cIsUpper = isupper(line[i]);
				char offset = cIsUpper ? 'A' : 'a';
				int keyIndex = (i - nonAlphaCharCount) % keyLen;
				int k = (cIsUpper ? toupper(newKey[keyIndex]) : tolower(newKey[keyIndex])) - offset;
				k = encipher ? k : -k;
				char ch = (char)((((line[i] + k) - offset) % 26 + 26) % 26 + offset);
				output += ch;
			}
			else
			{
				output += line[i];
				++nonAlphaCharCount;
			}
		}
		line = output;
	}
	catch (int e)
	{

	}
}

void Crypto::vigenereEncrypt(std::string &input)
{
	vigenereCipher(input, true);
}

void Crypto::vigenereDecrypt(std::string &input)
{
	vigenereCipher(input, false);
}



