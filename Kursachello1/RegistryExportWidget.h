#ifndef REGISTRYEXPORTWIDGET_H
#define REGISTRYEXPORTWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QSettings>
#include <QDir>
#include <QDate>
#include <windows.h>

namespace Ui {
class RegistryExportWidget;
}

class RegistryExportWidget : public QWidget{
	Q_OBJECT

	public:
		explicit RegistryExportWidget(QWidget *parent = 0);
		~RegistryExportWidget();

	public slots:
		void addSubHives(QTreeWidgetItem *item);

	private slots:
		void on_exportButton_clicked();

	private:
		Ui::RegistryExportWidget *ui;
		QString getHivePath(QTreeWidgetItem* item);
};

#endif // REGISTRYEXPORTWIDGET_H
