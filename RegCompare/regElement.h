#pragma once
#include <string>
#include <vector>

using namespace std;

class RegElement
{
	wstring regPath;
	wstring defaultValue;
	vector< wstring > dataItems;

public:
	RegElement& operator=(RegElement& element);
	wstring& getData(int i){
		return dataItems[i];
	}
	int getDataSize(){
		return dataItems.size();
	}
	bool isEmpty(){
		return regPath.size()==1 ? true : false;
	}
	void setRegPath(wstring path){
		regPath = path;
	}
	void setDefValue(wstring value){
		defaultValue = value;
	}
	void pushData(wstring data){
		dataItems.push_back(data);
	}
	wstring& getRegPath(){
		return regPath;
	}
	wstring& getDefaultValue(){
		return defaultValue;
	}
	void clearAll(){
		regPath.clear();
		defaultValue.clear();
		dataItems.clear();
	}
	RegElement(void);
	~RegElement(void);
};