#include <stdlib.h>
#include <iostream>
#include <string>

int main(){
	std::string pathOfBranch, directory, name, command;
  // Проверка, доступен ли командный процессор
	if ( system(NULL) ) 
		std::cout << "CMD can be used\n";
	else 
		exit (1);                                      // выход из программы
	//std::cout << "Enter the path of the exported registry branch:"<<std::endl;
	//std::cin >> pathOfBranch;
	
	//std::cout << "Enter the folder to save:" <<std::endl;
	//std::cin >> directory;

	//std::cout << "Enter the name of the file:" <<std::endl;
	//std::cin >> name;

	pathOfBranch = "HKCU\\Software\\QtProject";
	directory = "C:\\";
	name = "reg6.reg";

	command = "REG EXPORT " + pathOfBranch + " " + directory + name;
	std::cout << command <<std::endl;

	system(command.c_str());
	return 0;
}