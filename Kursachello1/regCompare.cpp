#include "regCompare.h"

void RegCompare::compareFiles(const QString& name1, const QString& name2){
	RegElement element1, element2;
	bool end1Fl = false, end2Fl = false, fl = false;
	int subKeysCount = 0, currentLevel = 0;

	QFile file1(name1);
	if (!file1.exists())
		return;
	file1.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream stream1(&file1);

	QFile file2(name2);
	if (!file2.exists())
		return;
	file2.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream stream2(&file2);

    stream1.setCodec("UTF-8");
	stream2.setCodec("UTF-8");

	while(true){
		if(!fl){
			if(!read(stream1, element1)){
				end1Fl = true;
				break;
			}
			if(!read(stream2, element2)){
				end2Fl = true;
				break;
			}
		}
		else
			fl = false;
// 0 - elements are not equal
// 1 - RegPath are not equal
// 2 - default values are not equal
// 3 - values of hives are not equal

        switch(element1.compare(element2)){
			case 0:
				break;
			case 1:
				if(element1.getRegPath().compare(element2.getRegPath()) > 0){
					currentLevel = element2.getLevel();
					newHives.push_back(element2);
					while(true){
                        if(!read(stream2, element2)){
							end2Fl = true;
							break;
						}
						if(element2.getLevel() > currentLevel)
							subKeysCount++;
						else
							break;
					}
					newHives.last().setSubKeysCount(subKeysCount);
					if(element1.getRegPath().compare(element2.getRegPath())){
						currentLevel = element1.getLevel();
						deletedHives.push_back(element1);
						subKeysCount = 0;
						while(true){
							if(!read(stream1, element1)){
								end1Fl = true;
								break;
							}
							if(element1.getLevel() > currentLevel)
								subKeysCount++;
							else
								break;
						}
						deletedHives.last().setSubKeysCount(subKeysCount);
					}
				}
				else{
					currentLevel = element1.getLevel();
					deletedHives.push_back(element1);
					while(true){
                        if(!read(stream1, element1)){
							end1Fl = true;
							break;
						}
						if(element1.getLevel() > currentLevel)
							subKeysCount++;
						else
							break;
					}
					deletedHives.last().setSubKeysCount(subKeysCount);
					if(element1.getRegPath().compare(element2.getRegPath())){
						currentLevel = element2.getLevel();
						subKeysCount = 0;
						newHives.push_back(element2);
						while(true){
							if(!read(stream2, element2)){
								end2Fl = true;
								break;
							}
							if(element2.getLevel() > currentLevel)
								subKeysCount++;
							else
								break;
						}
						newHives.last().setSubKeysCount(subKeysCount);
					}
				}
				fl = true;
				subKeysCount = 0;
				break;
			case 2:
				changedDefaultValues.push_back(element2);
				break;
			case 3:
				changedKeys.push_back(element2);
				break;				
		}
	}
	if(end1Fl){
		while(true){
            if(!read(stream2, element2))
				break;
			newHives.push_back(element2);
		}
	}
	if(end2Fl){
        while(true){
			deletedHives.push_back(element1);
            if(!read(stream1, element1))
				break;
		}
	}

	for(int i = 0; i < newHives.size(); i++)
		for(int j = 0; j < deletedHives.size(); j++)
			if(!newHives[i].compare(deletedHives[j])){
				newHives.remove(i--);
				deletedHives.remove(j);
				break;
			}
	for(int i = 0; i < newHives.size(); i++)
		for(int j = 0; j < deletedHives.size(); j++)
			if(newHives[i].checkDifferences(deletedHives[j])){
				renamedKeys.push_back(newHives[i]);
				newHives.remove(i--);
				deletedHives.remove(j);
				break;
			}

	file1.close();
	file2.close();
}

bool RegCompare::read(QTextStream &stream, RegElement& element){
	element.clearAll();
	QString buf = stream.readLine(300);
	if(!buf.size())
		return false;
	if(buf[0] == L'['){
		element.setRegPath(buf);
		buf = stream.readLine(300);
		if(!buf.size())
			return true;
	}
	if(buf[0] == L'@'){
		element.setDefValue(buf);
		buf = stream.readLine(300);
		if(!buf.size())
			return true;
	}
	if(buf[0] == L'"')
		element.pushData(buf);
	while(true){
		buf = stream.readLine(300);
		if(!buf.size())
			return true;
		else
			element.pushData(buf);
		}
}

void RegCompare::clear(){
	newHives.clear();
	deletedHives.clear();
	renamedKeys.clear();
	changedDefaultValues.clear();
	changedKeys.clear();
}

RegCompare::RegCompare(void){
}

RegCompare::~RegCompare(void){
}
