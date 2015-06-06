#include "RegThread.h"

RegThread::RegThread(QObject *parent) :
	QThread(parent){
	finishFl = false;
}

void RegThread::run(){
	RegCompare rc;

	qDebug("Start thread  - ололок");
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	cif.dwFlags = STARTF_USESHOWWINDOW;
	cif.wShowWindow = SW_HIDE;
	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;
	QString regCommand = "C:\\Windows\\System32\\reg.exe";

	QDir directory(QApplication::applicationDirPath());
	directory.cd("Temp");
	directory.cd(rootKeyStr);
	QString fileName;
	QStringList tmpList = pathOfKey.split("\\");
	if(tmpList[0].size()){
		for(int i = 0; i < tmpList.size(); i++){
			if(i == tmpList.size()-1)
				fileName = tmpList[i];
			else{
				directory.mkdir(tmpList[i]);
				directory.cd(tmpList[i]);
			}
		}
	}
	else
		fileName = rootKeyStr;

	QString commandExport = "REG EXPORT ";
	QString pathOfBranch;
	if(pathOfKey.size())
		pathOfBranch = rootKeyStr + "\\" + pathOfKey + ' ';
	else
		pathOfBranch = rootKeyStr + ' ';
	QString fileDir = directory.absolutePath() + "/" + fileName +".reg";
	QString command = commandExport + pathOfBranch + fileDir;
	QString bufFileDir = directory.absolutePath() + "/" + fileName + "(1)" +".reg";
	QString newCommand = commandExport + pathOfBranch + bufFileDir;
	wchar_t *wCommand = (wchar_t*)command.utf16();
	wchar_t *wCommandNew = (wchar_t*)newCommand.utf16();

	QFile::remove(fileDir);
	QFile::remove(bufFileDir);

	HKEY rootKey;
	if(rootKeyStr == "HKCU")
		rootKey = HKEY_CURRENT_USER;
	else
		if(rootKeyStr == "HKU")
			rootKey = HKEY_USERS;
		else
			if(rootKeyStr == "HKLM")
				rootKey = HKEY_LOCAL_MACHINE;
			else
				if(rootKeyStr == "HKCR")
					rootKey = HKEY_CLASSES_ROOT;
				else
					if(rootKeyStr == "HKCC")
						rootKey = HKEY_CURRENT_CONFIG;
					else{
						qDebug("ERROR! Can't find root key");
						quit();
					}

	if(RegOpenKeyEx(rootKey, pathOfKey.toStdWString().c_str(), NULL,
		KEY_READ | KEY_WOW64_64KEY, &hTestKey) == ERROR_SUCCESS){

		if(!CreateProcess(regCommand.toStdWString().c_str(), wCommand,
			NULL, NULL, FALSE, NULL, NULL, NULL, &cif,&pi1))
				quit();

		hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		if(!hEvent){
			qDebug("Event Error!");
		}

		WaitForSingleObject(pi1.hProcess, 100000);

		if(RegNotifyChangeKeyValue(hTestKey, true,
			REG_NOTIFY_CHANGE_LAST_SET | REG_NOTIFY_CHANGE_NAME, hEvent, true) != ERROR_SUCCESS){
			qDebug("RNCKV ERROR1!");
			quit();
		}
		emit setRes("Мониторинг ветви " + pathOfBranch + " запущен\n");
		while(!finishFl){
			if(WaitForSingleObject(hEvent, 100) == WAIT_OBJECT_0){

				if(!CreateProcess(regCommand.toStdWString().c_str(), wCommandNew,
					NULL, NULL, FALSE, NULL, NULL, NULL, &cif,&pi2))
							quit();
				WaitForSingleObject(pi2.hProcess, 100000);

				rc.clear();
				rc.compareFiles(fileDir, bufFileDir);
				if(rc.checkChanges()){
					if(rc.newHives.size()){
						emit setRes(QTime::currentTime().toString() + "\nНовые ветви реестра:");
						for(int i = 0; i < rc.newHives.size(); i++)
							emit setRes(rc.newHives[i].getRegPath());
						emit setRes("");
					}
					if(rc.deletedHives.size()){
						emit setRes(QTime::currentTime().toString() + "\nУдаленные ветви реестра:");
						for(int i = 0; i < rc.deletedHives.size(); i++)
							emit setRes(rc.deletedHives[i].getRegPath());
						emit setRes("");
					}
					if(rc.changedDefaultValues.size()){
						emit setRes(QTime::currentTime().toString()+"\nВетви с измененными дефолтными значениями:");
						for(int i = 0; i < rc.changedDefaultValues.size(); i++){
							emit setRes(rc.changedDefaultValues[i].getRegPath());
							emit setRes(rc.changedDefaultValues[i].getDefaultValue());
						}
						emit setRes("");
					}
					if(rc.changedKeys.size()){
						emit setRes(QTime::currentTime().toString()+"\nВетви с измененными значениями:");
						for(int i = 0; i < rc.changedKeys.size(); i++){
							emit setRes(rc.changedKeys[i].getRegPath());
							for(int j = 0; j < rc.changedKeys[i].getDataSize(); j++)
								emit setRes(rc.changedKeys[i].getData(j));
						}
						emit setRes("");
					}
					if(rc.renamedKeys.size()){
						emit setRes(QTime::currentTime().toString()+ "\nПереименованные ключи:");
						for(int i = 0; i < rc.renamedKeys.size(); i++){
							emit setRes(rc.renamedKeys[i].getRegPath());
						}
						emit setRes("");
					}

					QFile::remove(fileDir);
					QFile::rename(bufFileDir, fileDir);
				}
				else{
					QFile::remove(bufFileDir);
				}

				RegNotifyChangeKeyValue(hTestKey, true,
					REG_NOTIFY_CHANGE_LAST_SET | REG_NOTIFY_CHANGE_NAME, hEvent, true);
			}
		}
	}
	else{
		qDebug("ERROR");
	}
	finishFl = false;
	quit();
}

RegThread::~RegThread(){
	finishFl = true;
	RegCloseKey(hTestKey);
	CloseHandle(hEvent);
}
