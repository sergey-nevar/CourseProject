#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include <QWidget>
#include <windows.h>
#include <QFile>
#include <QDir>
#include <QDate>
#include <QTextStream>
#include "regCompare.h"

namespace Ui {
class MonitorWidget;
}

class MonitorWidget : public QWidget{
	Q_OBJECT

	public:
		explicit MonitorWidget(QWidget *parent = 0);
		~MonitorWidget();
		void setResText(QString resStr);

	private slots:
		void on_clerBufButton_clicked();
		void on_regeditButton_clicked();
		void on_stopButton_clicked();
		void on_startButton_clicked();

	signals:
		void stopThread();
		void startThread();

	private:
		Ui::MonitorWidget *ui;
};

#endif // MONITORWIDGET_H
