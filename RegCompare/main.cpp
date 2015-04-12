#include <iostream>
#include <fstream>
#include <string>
#include "regCompare.h"
//программа обрабатывает русские символы как окончание строки
using namespace std;

int main(){
	RegCompare cmp;
	cmp.compareShots("C://reg7.reg", "C://reg8.reg");	
	cmp.printResults();
	return 0;
}