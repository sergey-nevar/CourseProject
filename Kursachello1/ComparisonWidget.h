#ifndef COMPARISONWIDGET_H
#define COMPARISONWIDGET_H

#include <QWidget>
#include "regCompare.h"
#include <QFileDialog>
#include <QTime>

namespace Ui {
class ComparisonWidget;
}

class ComparisonWidget : public QWidget{
	Q_OBJECT

	public:
		explicit ComparisonWidget(QWidget *parent = 0);
		~ComparisonWidget();

	private:
		Ui::ComparisonWidget *ui;

	private slots:
		void on_pushButtonFile1_clicked();
		void on_pushButtonFile2_clicked();
		void on_pushButton_clicked();
};

#endif // COMPARISONWIDGET_H
