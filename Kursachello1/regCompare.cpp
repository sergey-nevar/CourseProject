#include "regCompare.h"

void RegCompare::compareShots(char *name1, char *name2){
	RegElement element1, element2;
    bool end1Fl = false, end2Fl = false;
    QFile file1, file2;
    QTextStream stream1, stream2;

    file1.setFileName(name1);
        if (!file1.exists())
               return;
    file1.open(QIODevice::ReadOnly | QIODevice::Text);
    stream1.setDevice(&file1);

    file2.setFileName(name2);
        if (!file2.exists())
               return;
    file2.open(QIODevice::ReadOnly | QIODevice::Text);
    stream2.setDevice(&file2);

    stream1.setCodec("UTF-8");
    stream2.setCodec("UTF-8");

    while(true){
        element1.clearAll();
        element2.clearAll();
        if(!read(stream1, element1)){
            end1Fl = true;
            break;
        }
        if(!read(stream2, element2)){
            end2Fl = true;
            break;
        }
// 0 - elements are not equal
// 1 - RegPath are not equal
// 2 - default values are not equal
// 3 - values of hives are not equal

		switch(compareElements(element1, element2)){
			case 0:
				break;
			case 1:
				if(element1.getRegPath().compare(element2.getRegPath()) > 0){
					do{
						newHives.push_back(element2);
						element2.clearAll();
                        if(!read(stream2, element2)){
							end2Fl = true;
							break;
						}	
					}while(element1.getRegPath().compare(element2.getRegPath()) > 0);
					if(element1.getRegPath().compare(element2.getRegPath()))
						deletedHives.push_back(element1);
				}
				else{
					do{
						deletedHives.push_back(element1);
						element1.clearAll();
                        if(!read(stream1, element1)){
							end1Fl = true;
							break;
						}
					}while(element1.getRegPath().compare(element2.getRegPath()) < 0);
					if(element1.getRegPath().compare(element2.getRegPath()))
						newHives.push_back(element2);
				}
				break;
			case 2:
                changedDefaultValues.push_back(element1);
				break;
			case 3:
				changedKeys.push_back(element1);
				break;				
		}
	}
	if(end1Fl){
        while(true){
			element2.clearAll();
            if(!read(stream2, element2))
				break;
			newHives.push_back(element2);
		}
	}
	if(end2Fl){
        while(true){
			deletedHives.push_back(element1);
			element1.clearAll();
            if(!read(stream1, element1))
				break;
		}
	}
}

bool RegCompare::read(QTextStream &stream, RegElement& element){
    QString buf = stream.readLine(350);
    if(!buf.size())
        return false;
    if(buf[0] == L'['){
        element.setRegPath(buf);
        buf = stream.readLine(350);
        if(!buf.size())
            return true;
    }
    if(buf[0] == L'@'){
        element.setDefValue(buf);
        buf = stream.readLine(350);
        if(!buf.size())
            return true;
    }
    if(buf[0] == L'"')
        element.pushData(buf);
    while(true){
        buf = stream.readLine(350);
        if(!buf.size())
            return true;
        else
            element.pushData(buf);
        }
}

int RegCompare::compareElements(RegElement& element1, RegElement& element2){
	if(element1.getRegPath() != element2.getRegPath())
		return 1;
	if(element1.getDefaultValue() != element2.getDefaultValue())
		return 2;
	if(element1.getDataSize() != element2.getDataSize())
		return 3;
	for(int i = 0; i < element1.getDataSize(); i++){
		if(element1.getData(i) != element2.getData(i))
			return 3;
	}
	return 0;
}

RegCompare::RegCompare(void)
{
}

RegCompare::~RegCompare(void)
{
}
