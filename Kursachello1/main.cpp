#include "mainwindow.h"
#include "regCompare.h"
#include "RegThread.h"
#include <QApplication>
#include <QFileInfo>
#include <QFile>
#include <QSettings>

int main(int argc, char *argv[]){
	QApplication a(argc, argv);
	a.addLibraryPath(a.applicationDirPath()+"/plugins/platforms");
	MainWindow w;

	QDir directory(QApplication::applicationDirPath());
	directory.mkdir("Temp");
	directory.mkdir("Snapshots");
	directory.mkdir("Logs");
	directory.cd("Temp");
	directory.mkdir("HKCU");
	directory.mkdir("HKLM");
	directory.mkdir("HKU");
	directory.mkdir("HKCR");
	directory.mkdir("HKCC");

	RegThread thread;
	thread.setRootKey("HKCU");
	thread.setPathOfKey("");
	QObject::connect(&thread, SIGNAL(returnResults(QString)),
					&w, SLOT(setResults(QString)));
	QObject::connect(&w, SIGNAL(closeWindow()),
					&thread, SLOT(finishThread()));
	QObject::connect(&w, SIGNAL(startThread()),
					 &thread, SLOT(start()));
	thread.start();

	RegThread thread1;
	thread1.setRootKey("HKCC");
	thread1.setPathOfKey("");
	QObject::connect(&thread1, SIGNAL(returnResults(QString)),
					&w, SLOT(setResults(QString)));
	QObject::connect(&w, SIGNAL(closeWindow()),
					&thread1, SLOT(finishThread()));
	QObject::connect(&w, SIGNAL(startThread()),
					 &thread1, SLOT(start()));
	thread1.start();

	RegThread thread2;
	thread2.setRootKey("HKCR");
	thread2.setPathOfKey("");
	QObject::connect(&thread2, SIGNAL(returnResults(QString)),
					&w, SLOT(setResults(QString)));
	QObject::connect(&w, SIGNAL(closeWindow()),
					&thread2, SLOT(finishThread()));
	QObject::connect(&w, SIGNAL(startThread()),
					 &thread2, SLOT(start()));
	thread2.start();

	QSettings settings("HKEY_LOCAL_MACHINE", QSettings::NativeFormat);
	QStringList keys = settings.childGroups();
	RegThread threadsHKLM[keys.size()];
	qDebug(QString("%1").arg(keys.size()).toLocal8Bit());
	for(int i = 0; i < keys.size(); i++){
		threadsHKLM[i].setRootKey("HKLM");
		threadsHKLM[i].setPathOfKey(keys[i]);
		QObject::connect(&threadsHKLM[i], SIGNAL(returnResults(QString)),
						&w, SLOT(setResults(QString)));
		QObject::connect(&w, SIGNAL(closeWindow()),
						&threadsHKLM[i], SLOT(finishThread()));
		QObject::connect(&w, SIGNAL(startThread()),
						 &threadsHKLM[i], SLOT(start()));
		threadsHKLM[i].start();
	}

	QSettings settings1("HKEY_USERS", QSettings::NativeFormat);
	keys = settings1.childGroups();
	RegThread threadsHKU[keys.size()];
	qDebug(QString("%1").arg(keys.size()).toLocal8Bit());
	for(int i = 0; i < keys.size(); i++){
		threadsHKU[i].setRootKey("HKU");
		threadsHKU[i].setPathOfKey(keys[i]);
		QObject::connect(&threadsHKU[i], SIGNAL(returnResults(QString)),
						&w, SLOT(setResults(QString)));
		QObject::connect(&w, SIGNAL(closeWindow()),
						&threadsHKU[i], SLOT(finishThread()));
		QObject::connect(&w, SIGNAL(startThread()),
						 &threadsHKU[i], SLOT(start()));
		threadsHKU[i].start();
	}

	w.show();
    return a.exec();
}
