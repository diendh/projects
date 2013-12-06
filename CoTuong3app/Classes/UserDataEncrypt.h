/*
 * DataEncrypt.h
 *
 *  Created on: Apr 20, 2013
 *      Author: QuyetNguyen
 */

#ifndef DATAENCRYPT_H_
#define DATAENCRYPT_H_
#include "cocos2d.h"
USING_NS_CC;

class DataEncrypt {
protected:
	tinyxml2::XMLDocument* data;
	unsigned char* keyData;

	char* externalFileData;

	void createNewData();
	bool readFromDataFile();
	bool readFromExternalFile();
	bool parseXMLData(unsigned long nSize,const char* dataBuffer);

	void createKey();
public:
	DataEncrypt();
	virtual ~DataEncrypt();
	void initData();
	void save();

	static DataEncrypt* share();

	bool    getBoolForKey(const char* pKey, bool defaultValue);
	int     getIntegerForKey(const char* pKey, int defaultValue);
	float    getFloatForKey(const char* pKey, float defaultValue);
	double  getDoubleForKey(const char* pKey, double defaultValue);
	std::string getStringForKey(const char* pKey, const std::string & defaultValue);
	const char* getCStringForKey(const char* pKey);

	void    setBoolForKey(const char* pKey, bool value);
	void    setIntegerForKey(const char* pKey, int value);
	void    setFloatForKey(const char* pKey, float value);
	void    setDoubleForKey(const char* pKey, double value);
	void    setStringForKey(const char* pKey, const std::string & value);
};

#endif /* DATAENCRYPT_H_ */
