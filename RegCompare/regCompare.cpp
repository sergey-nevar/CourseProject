#include "regCompare.h"

void RegCompare::compareShots(char *name1, char *name2){
	RegElement element1, element2;
	bool end1Fl = false, end2Fl = false, cmpCurFl = false;

	shot1.open(name1, ios::in | ios::beg);
	if(!shot1.is_open())
		return;
	shot2.open(name2, ios::in | ios::beg);
	if(!shot2.is_open())
		return;

	while(1){
		if(!cmpCurFl){
			element1.clearAll();
			element2.clearAll();
			if(!read(shot1, element1)){
				end1Fl = true;
				break;
			}
			if(!read(shot2, element2)){
				end2Fl = true;
				break;
			}	
		}
		else cmpCurFl = false;

// 0 - элементы равны
// 1 - не равны пути ветвей
// 2 - не равны дефолтные значения ветвей
// 3 - отличаются значения ключей в ветви

		switch(compareElements(element1, element2)){
			case 0:
				break;
			case 1:
				if(element1.getRegPath().compare(element2.getRegPath()) > 0){
					do{
						newHives.push_back(element2);
						element2.clearAll();
						if(!read(shot2, element2)){
							end2Fl = true;
							break;
						}	
					}while(element1.getRegPath().compare(element2.getRegPath()) > 0);
					if(element1.getRegPath().compare(element2.getRegPath()))
						deletedHives.push_back(element1);
					else
						cmpCurFl = true;
				}
				else{
					do{
						deletedHives.push_back(element1);
						element1.clearAll();
						if(!read(shot1, element1)){
							end1Fl = true;
							break;
						}
					}while(element1.getRegPath().compare(element2.getRegPath()) < 0);
					if(element1.getRegPath().compare(element2.getRegPath()))
						newHives.push_back(element2);
					else
						cmpCurFl = true;
				}
				break;
			case 2:
				changedDefaultValues.push_back(element2);
				break;
			case 3:
				changedKeys.push_back(element1);
				break;				
		}
	}
	if(end1Fl){
		while(1){	
			element2.clearAll();
			if(!read(shot2, element2))
				break;
			newHives.push_back(element2);
		}
	}
	if(end2Fl){
		while(1){
			deletedHives.push_back(element1);
			element1.clearAll();
			if(!read(shot1, element1))
				break;
		}
	}
}

bool RegCompare::read(wfstream& shot, RegElement& element){
	wstring buf;
	if(getline(shot, buf).eof())
		return false;
	if(buf[1] == L'\r')
		return true;
	if(buf[1] == L'[')
		element.setRegPath(buf);
	if(getline(shot, buf).eof())
		return false;
	if(buf[1] == L'\r')
		return true;
	if(buf[1] == L'@')
		element.setDefValue(buf);
	if(buf[1] == L'"')
		element.pushData(buf);
	if(!element.isEmpty())
		while(1){
			if(getline(shot, buf).eof())
				return false;
			if(buf[1] != L'\r')
				element.pushData(buf);
			else 
				break;
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

void RegCompare::printResults(){
	cout << "New hives" <<endl;
	for(int i = 0; i < newHives.size(); i++)
		wcout << newHives[i].getRegPath()<<endl;

	cout << endl<< "Deleted hives" <<endl;
	for(int i = 0; i < deletedHives.size(); i++)
		wcout << deletedHives[i].getRegPath()<<endl;

	cout <<endl << "Changed default values" <<endl;
	for(int i = 0; i < changedDefaultValues.size(); i++)
		wcout << changedDefaultValues[i].getDefaultValue()<<endl;

	cout <<endl << "Changed keys" <<endl;
	for(int i = 0; i < changedKeys.size(); i++)
		wcout << changedKeys[i].getRegPath()<<endl;
}