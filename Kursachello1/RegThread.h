#ifndef REGTHREAD_H
#define REGTHREAD_H

#include <QThread>
#include <QApplication>
#include <windows.h>
#include <QtDebug>
#include <QFile>
#include <QDir>
#include <QTime>
#include <QTextEdit>
#include "regCompare.h"

class RegThread : public QThread{
	Q_OBJECT

	bool finishFl;
	HKEY hTestKey;
	HANDLE hEvent;
	QString rootKeyStr;
	QString pathOfKey;
	QDir directory;

	public:
		explicit RegThread(QObject *parent = 0);
		void run();
		void setRootKey(QString key){
			rootKeyStr = key;
		}
		void setPathOfKey(QString path){
			pathOfKey = path;
		}
		~RegThread();

	signals:
		void returnResults(QString);
	public slots:
		void finishThread(){
			finishFl = true;
			RegCloseKey(hTestKey);
			CloseHandle(hEvent);
		}
		void setRes(QString str){
			emit returnResults(str);
		}
};

#endif // REGTHREAD_H
