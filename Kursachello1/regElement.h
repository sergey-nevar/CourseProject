#pragma once
#include <QString>
#include <QVector>
#include <QStringList>

class RegElement{
	QString regPath;
	QString defaultValue;
	QVector< QString > dataItems;
	int subKeysCount;

	public:
		QString& getData(int i){
			return dataItems[i];
		}
		int getDataSize(){
			return dataItems.size();
		}
		void setRegPath(QString path){
			regPath = path;
		}
		void setDefValue(QString value){
			defaultValue = value;
		}
		void pushData(QString data){
			dataItems.push_back(data);
		}
		QString& getRegPath(){
			return regPath;
		}
		QString& getDefaultValue(){
			return defaultValue;
		}
		void setSubKeysCount(int count){
			subKeysCount = count;
		}
		void clearAll(){
			regPath.clear();
			defaultValue.clear();
			dataItems.clear();
		}
		int getLevel(){
			QStringList list = regPath.split("\\");
			return list.size();
		}
		int getSubkeysCount(){
			return subKeysCount;
		}
		bool checkDifferences(RegElement& element2);
		int compare(RegElement& element2);	
		RegElement(void);
		~RegElement(void);
};
