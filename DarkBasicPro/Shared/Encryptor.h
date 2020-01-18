#pragma once

#include <stdint.h>
#include <string>


class CEncryptor
{
public:
	CEncryptor(const uint32_t UniqueKeyValue);
	virtual ~CEncryptor();

	bool EncryptFileData(std::string filebuffer, const uint32_t filebuffersize, const bool bEncryptIfTrue);

	const uint32_t GetUniqueKey() { return UniqueKey; }
	void SetUniqueKey(const uint32_t UniqueKeyValue) { UniqueKey = UniqueKeyValue; }

private:
	uint32_t UniqueKey;
};