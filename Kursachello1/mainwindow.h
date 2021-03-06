#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QStackedWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ComparisonWidget.h"
#include "MonitorWidget.h"
#include "regCompare.h"
#include "RegistryExportWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private slots:
		void on_action_triggered();
		void on_action_2_triggered();
		void on_makeExport_triggered();

	private:
		Ui::MainWindow *ui;
		MonitorWidget* monitor;
		ComparisonWidget *comparisonWidget;
		RegistryExportWidget *exportWidget;

	public slots:
		void setResults(QString resultString){
			monitor->setResText(resultString);
		}
		void stopThread();
		void startMonitoring();

	signals:
		void closeWindow();
		void startThread();
};

#endif // MAINWINDOW_H
