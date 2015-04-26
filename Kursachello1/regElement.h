#pragma once
#include <QString>
#include <QVector>

class RegElement
{
    QString regPath;
    QString defaultValue;
    QVector< QString > dataItems;

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
	void clearAll(){
		regPath.clear();
		defaultValue.clear();
		dataItems.clear();
	}
	RegElement(void);
	~RegElement(void);
};
