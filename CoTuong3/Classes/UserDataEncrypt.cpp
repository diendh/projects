/*
 * DataEncrypt.cpp
 *
 *  Created on: Apr 20, 2013
 *      Author: QuyetNguyen
 */

#include "UserDataEncrypt.h"
#include "AES/aes.h"
#define FILENAME "UserData.g9d"
#define ROOT_NAME "UserData"

/*GameName = pikachu-gamengon*/
/*MD5 x 2 = folder*/
/*MD5 x 3 = file name*/

#define EXTERNAL_PATH ".profv/.27260db4c2fbeeca8e2d976ed1ee5be9/"
#define EXTERNAL_FILE_NAME "44be75ac56fb9dd901bcd49dcd958a3e"

#define AES_KEY_SIZE_BITS 256

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"{
#include "jni/JniHelper.h"
#include "jni.h"
	std::string jniCreateFolderExternalStorage(const char* path){
		JniMethodInfo method;
		bool b = JniHelper::getStaticMethodInfo(method,"vn.g9game.cocos2d.libs.Storage","requestCreateFolderExternalStorage","(Ljava/lang/String;)Ljava/lang/String;");
		if(b){
			jstring path_ = method.env->NewStringUTF(path);
			jstring absolutePath = (jstring)method.env->CallStaticObjectMethod(method.classID,method.methodID,path_);

			std::string cString = JniHelper::jstring2string(absolutePath);
			CCLog("xxxx=%s",cString.c_str());

			method.env->DeleteLocalRef(method.classID);
			method.env->DeleteLocalRef(path_);
			method.env->DeleteLocalRef(absolutePath);

			return cString;
		}
	}

}
#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) */

inline tinyxml2::XMLElement* getNodeForKey(const char* pKey, tinyxml2::XMLElement* rootNode){
    tinyxml2::XMLElement* curNode = NULL;
	
	// find the node
	curNode = rootNode->FirstChildElement();
	while (NULL != curNode)
	{
		const char* nodeName = curNode->Value();
		if (!strcmp(nodeName, pKey))
		{
			break;
		}

		curNode = curNode->NextSiblingElement();
	}
	return curNode;
}

inline void setValueForKey(const char* pKey, tinyxml2::XMLDocument* doc, const char* pValue){
	tinyxml2::XMLElement* rootNode  = doc->RootElement();
	if (!rootNode)
	{
		return;
	}
	tinyxml2::XMLElement* node = getNodeForKey(pKey, rootNode);
	// if node exist, change the content
	if (node){
		if (node->FirstChild()){
			node->FirstChild()->SetValue(pValue);
		}
		else{
			tinyxml2::XMLText* content = doc->NewText(pValue);
			node->LinkEndChild(content);
		}
	}
	else{
		if (rootNode){
			tinyxml2::XMLElement* tmpNode = doc->NewElement(pKey);
			rootNode->LinkEndChild(tmpNode);
			tinyxml2::XMLText* content = doc->NewText(pValue);
			tmpNode->LinkEndChild(content);
		}
	}
}

/******************/
static DataEncrypt s_pDataEncrypt;
static bool s_bDataEncrypt = true;

DataEncrypt* DataEncrypt::share(){
	if(s_bDataEncrypt){
		s_pDataEncrypt.initData();
		s_bDataEncrypt = false;
	}
	return &s_pDataEncrypt;
}

DataEncrypt::DataEncrypt() {
	// TODO Auto-generated constructor stub
	data = NULL;
	externalFileData = NULL;
}

DataEncrypt::~DataEncrypt() {
	// TODO Auto-generated destructor stub
	CC_SAFE_DELETE(data);
	CC_SAFE_DELETE(externalFileData);
}

void DataEncrypt::initData(){
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	std::string externalFile = jniCreateFolderExternalStorage(EXTERNAL_PATH).append("/").append(EXTERNAL_FILE_NAME);
//	externalFileData = new char[externalFile.size()+1];
//	strcpy(externalFileData,externalFile.c_str());
//	CCLog("path = %s",externalFileData);
//#else
//	//std::string externalFile = FileUtils::getInstance()->getWritablePath().append(FILENAME);
//#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) */
	
	//read data
	if(!readFromDataFile()){
//		if(!readFromExternalFile())
		{
			this->createNewData();
		}
	}
}

void DataEncrypt::createNewData(){
	data = new tinyxml2::XMLDocument();

	tinyxml2::XMLDeclaration *pDeclaration = data->NewDeclaration("1.0");
	data->LinkEndChild(pDeclaration);

	tinyxml2::XMLElement *pRootEle = data->NewElement(ROOT_NAME);
	data->LinkEndChild(pRootEle);

	createKey();
}

void DataEncrypt::createKey(){
	srand(time(0));
	int keySize = AES_KEY_SIZE_BITS/8;
	keyData = new unsigned char[keySize];
	for(int i=0;i<keySize;i++){
		keyData[i] = rand();
	}
}



bool DataEncrypt::readFromDataFile(){
	std::string filePath =CCFileUtils::sharedFileUtils()->getWritablePath().append(FILENAME);
	FILE* file = fopen(filePath.c_str(),"r");
//	CCLOG("data file: %s", filePath.c_str());
	if(!file){
		return false;
	}
	fclose(file);
	/* read file */
	unsigned long nSize;
	const char* dataBuffer = (const char*)CCFileUtils::sharedFileUtils()->getFileData(filePath.c_str(), "rb", &nSize);
	parseXMLData(nSize,dataBuffer);
	return true;
}

bool DataEncrypt::readFromExternalFile(){
	if (!externalFileData)
	{
		return false;
	}
	FILE* file = fopen(externalFileData,"r");
//	CCLOG("external file data: %s", externalFileData);
	if(!file){
		return false;
	}
	fclose(file);
	/* read file */
	unsigned long nSize;
	const char* dataBuffer = (const char*)CCFileUtils::sharedFileUtils()->getFileData(externalFileData, "rb", &nSize);
	parseXMLData(nSize,dataBuffer);
	return true;
}

bool DataEncrypt::parseXMLData(unsigned long nSize,const char* dataBuffer){
	/* decrypt data */
	// read key
	int keySize = AES_KEY_SIZE_BITS/8;
	int dataSize = nSize-keySize;
	keyData = new unsigned char[keySize];
	memcpy(keyData,dataBuffer,keySize);
	AES_KEY decryptKey;
	AES_set_decrypt_key(keyData,AES_KEY_SIZE_BITS,&decryptKey);
	//decrypt

	unsigned char* input =(unsigned char*) dataBuffer+keySize;
	unsigned char* ouput= new unsigned char[dataSize];
	unsigned char* xmlBuffer = ouput;

	int blockCount = dataSize/AES_BLOCK_SIZE;
	for(int i=0;i<blockCount;i++){
		AES_decrypt(input,ouput,&decryptKey);
		input += AES_BLOCK_SIZE;
		ouput += AES_BLOCK_SIZE;
	}

	this->data = new tinyxml2::XMLDocument();
	this->data->Parse((char*)xmlBuffer);
//	CCLOG("xml buffer: %s", xmlBuffer);

	delete dataBuffer;

	return true;
}

void DataEncrypt::save(){
	tinyxml2::XMLPrinter* printer = new tinyxml2::XMLPrinter();
	data->Print(printer);
//	CCLOG("printer: %s", printer->CStr());

	int dataSize = printer->CStrSize();
	int bufferSize = ((dataSize%AES_BLOCK_SIZE) == 0 ? dataSize/AES_BLOCK_SIZE:dataSize/AES_BLOCK_SIZE+1)*AES_BLOCK_SIZE;


	unsigned char *inputBuffer = new unsigned char[bufferSize];
	memset(inputBuffer,0,bufferSize);
	memcpy(inputBuffer,printer->CStr(),dataSize);

	/* encrypt */
	AES_KEY encryptKey;
	AES_set_encrypt_key(keyData,AES_KEY_SIZE_BITS,&encryptKey);

	unsigned char* outputData = inputBuffer;
	int blockCount = bufferSize/AES_BLOCK_SIZE;
	for(int i=0;i<blockCount;i++){
		AES_encrypt(inputBuffer,inputBuffer,&encryptKey);
		inputBuffer +=AES_BLOCK_SIZE;
	}

	/* save to file */
	std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath().append(FILENAME);
	FILE* file = fopen(filePath.c_str(),"wt");
	fwrite(keyData,1,AES_KEY_SIZE_BITS/8,file);
	fwrite(outputData,1,bufferSize,file);
	fclose(file);

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	/* save to external data */
//	FILE* externalFile = fopen(externalFileData,"wt");
//	fwrite(keyData,1,AES_KEY_SIZE_BITS/8,externalFile);
//	fwrite(outputData,1,bufferSize,externalFile);
//	fclose(externalFile);
//#endif

	delete outputData;
}

bool DataEncrypt::getBoolForKey(const char* pKey, bool defaultValue){
	const char* value = NULL;
	tinyxml2::XMLElement* node =  getNodeForKey(pKey, data->RootElement());
	// find the node
	if (node && node->FirstChild()){
		value = (const char*)(node->FirstChild()->Value());
	}

	if (value){
			bool ret = (! strcmp(value, "true"));
			return ret;
	}
	return defaultValue;
}

int DataEncrypt::getIntegerForKey(const char* pKey, int defaultValue){
	const char* value = NULL;
	tinyxml2::XMLElement* node =  getNodeForKey(pKey, data->RootElement());
	// find the node
	if (node && node->FirstChild()){
		value = (const char*)(node->FirstChild()->Value());
	}

	if (value){
		int ret = atoi(value);
		return ret;
	}
	return defaultValue;
}

float DataEncrypt::getFloatForKey(const char* pKey, float defaultValue){
	return (float)getDoubleForKey(pKey,defaultValue);
}

double DataEncrypt::getDoubleForKey(const char* pKey, double defaultValue){
	const char* value = NULL;
	tinyxml2::XMLElement* node =  getNodeForKey(pKey, data->RootElement());
	// find the node
	if (node && node->FirstChild()){
		value = (const char*)(node->FirstChild()->Value());
	}

	if (value){
		double ret = atof(value);
		return ret;
	}
	return defaultValue;
}

std::string DataEncrypt::getStringForKey(const char* pKey, const std::string & defaultValue){
	const char* value = NULL;
	tinyxml2::XMLElement* rootNode = data->RootElement();
	if (!rootNode)
	{
		return defaultValue;
	}
	tinyxml2::XMLElement* node =  getNodeForKey(pKey, rootNode);
	// find the node
	if (node && node->FirstChild()){
		value = (const char*)(node->FirstChild()->Value());
	}

	if (value){
		std::string ret = std::string(value);
		return ret;
	}
	return defaultValue;
}

const char* DataEncrypt::getCStringForKey(const char* pKey){
	const char* value = NULL;
	tinyxml2::XMLElement* node =  getNodeForKey(pKey, data->RootElement());
	// find the node
	if (node && node->FirstChild()){
		value = (const char*)(node->FirstChild()->Value());
		return value;
	}

	return NULL;
}

void DataEncrypt::setBoolForKey(const char* pKey, bool value){
	if (value == true){
		setStringForKey(pKey, "true");
	}
	else{
		setStringForKey(pKey, "false");
	}
}

void DataEncrypt::setIntegerForKey(const char* pKey, int value){
	char str[50];
	memset(str,0,50);
	sprintf(str,"%d",value);
	setValueForKey(pKey,data,str);
}

void DataEncrypt::setFloatForKey(const char* pKey, float value){
	setDoubleForKey(pKey,value);
}

void DataEncrypt::setDoubleForKey(const char* pKey, double value){
	char str[50];
	memset(str,0,50);
	sprintf(str,"%f",value);
	setValueForKey(pKey,data,str);
}

void DataEncrypt::setStringForKey(const char* pKey, const std::string & value){
	setValueForKey(pKey,data,value.c_str());
}

