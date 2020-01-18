/** LEGACY CLASS
 * This entire class is not very good for encryption, potentially unstable, and a mess.
 * If encryption is needed, this should be replaced with a third party solution.
 */

#include "Encryptor.h"

#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>


CEncryptor::CEncryptor(const uint32_t UniqueKeyValue)
{
	UniqueKey = UniqueKeyValue;
}

CEncryptor::~CEncryptor()
{

}

bool CEncryptor::EncryptFileData(std::string filebuffer, const uint32_t filebuffersize, const bool bEncryptIfTrue)
{
	uint32_t UniqueKeyValue = UniqueKey;

	if (UniqueKeyValue > 0)
	{
		int8_t pNewKey[10];
		for (uint8_t n = 0; n < 8; n++)
		{
			uint8_t NewInt = (uint8_t)((UniqueKeyValue / (1 + n)) % 255);
			if (NewInt < 32)
			{
				NewInt = 32;
			}
			pNewKey[n] = NewInt;
		}

		// Key index
		uint32_t KeyIndex = 0;
		uint32_t KeyMax = (uint32_t)filebuffer.size();

		// Data span
		uint32_t Span = filebuffersize / 1024;
		
		// Changed from DWORD to vector
		std::vector<char> pPtr(filebuffer.begin(), filebuffer.end());
		std::vector<char> pPtrEnd(filebuffer.size() + filebuffersize);

		/*
		std::cout << "PreEncrypt:" << std::endl;
		for (int i = 0; i < pPtr.size(); i++)
		{
			std::cout << pPtr.at(i);
		}
		std::cout << std::endl;
		*/

		while (pPtr.size() < pPtrEnd.size())
		{
			// This does nothing.....
			uint32_t ActualIndex = (uint32_t)(KeyIndex / 2) * 2;
			uint32_t KeyValue = pNewKey[ActualIndex];

			int iKeyData = KeyValue;
			if (((float)KeyIndex / 3.0f) == (uint32_t)KeyIndex / 3)
			{
				iKeyData *= -1;
			}
			
			// Original equation but it was still being executed even though it was replaced
			//iKeyData = abs(iKeyData) % 32;
			iKeyData = UniqueKeyValue % 64;

			//std::cout << "Key max: " << KeyMax << " Key Index: " << KeyIndex << std::endl;

			for (int r = 0; r < iKeyData; r++)
			{
				if (bEncryptIfTrue)
				{
					if ((uint8_t)pPtr[ActualIndex] == 255)
					{
						pPtr[ActualIndex] = 0;
					}
					else
					{
						pPtr[ActualIndex] += 1;
					}
				}
				else
				{
					if ((uint8_t)pPtr[ActualIndex] == 0)
					{
						pPtr[ActualIndex] = (uint32_t)255;
					}
					else
					{
						pPtr[ActualIndex] -= 1;
					}
				}
			}

			pPtr.push_back(Span);
			KeyIndex++;

			if (KeyIndex > KeyMax)
			{
				KeyIndex = 0;
			}
		}

		/*
		std::cout << "PostEncrypt:" << std::endl;

		for (int i = 0; i < pPtr.size(); i++)
		{
			std::cout << pPtr.at(i);
		}
		std::cout << std::endl;
		*/
		// TODO: Check for memory leak
		//std::vector<char>().swap(pPtr);
		//std::vector<char>().swap(pPtrEnd);
	}

	return true;
}

