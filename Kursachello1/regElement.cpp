#include "regElement.h"

RegElement::RegElement(void){
	subKeysCount = 0;
}


RegElement::~RegElement(void){
}

int RegElement::compare(RegElement &element2){
    if(regPath != element2.getRegPath())
        return 1;
    if(defaultValue != element2.getDefaultValue())
        return 2;
    if(dataItems.size() != element2.getDataSize())
        return 3;
	for(int i = 0, size = dataItems.size(); i < size; i++){
        if(dataItems[i] != element2.getData(i))
            return 3;
    }
    return 0;
}

bool RegElement::checkDifferences(RegElement &element2){
	QStringList list1, list2;
	list1 = regPath.split("\\");
	list2 = element2.getRegPath().split("\\");
	if(list1.size() != list2.size())
		return false;
	if(subKeysCount != element2.getSubkeysCount())
		return false;
	for(int i = 0; i < list1.size()-1; i++){
		if(list1[i] != list2[i])
			return false;
	}
	return true;
}

