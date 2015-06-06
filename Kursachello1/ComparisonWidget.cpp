#include "ComparisonWidget.h"
#include "ui_ComparisonWidget.h"

ComparisonWidget::ComparisonWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ComparisonWidget){
	ui->setupUi(this);
	setLayout(ui->gridLayout);
	ui->lineEditFile1->setReadOnly(true);
	ui->lineEditFile2->setReadOnly(true);
}

ComparisonWidget::~ComparisonWidget(){
	delete ui;
}

void ComparisonWidget::on_pushButtonFile1_clicked(){
	QDir directory(QApplication::applicationDirPath());
	directory.cd("Snapshots");
	QString path = QFileDialog::getOpenFileName(0, "Открыть", directory.absolutePath(), "*.reg");  //изменить
	ui->lineEditFile1->setText(path);
}

void ComparisonWidget::on_pushButtonFile2_clicked(){
	QDir directory(QApplication::applicationDirPath());
	directory.cd("Snapshots");
	QString path = QFileDialog::getOpenFileName(0, "Открыть", directory.absolutePath(), "*.reg");   //изменить
	ui->lineEditFile2->setText(path);
}

void ComparisonWidget::on_pushButton_clicked(){
	ui->resultText->clear();
	if(ui->lineEditFile1->text().size() && ui->lineEditFile2->text().size()){
		RegCompare rc;

		rc.compareFiles(ui->lineEditFile1->text(), ui->lineEditFile2->text());

		if(rc.newHives.size()){
			ui->resultText->append("Новые ветви реестра:");
			for(int i = 0; i < rc.newHives.size(); i++){
				ui->resultText->append(rc.newHives[i].getRegPath());
			}
			ui->resultText->append("");
		}

		if(rc.deletedHives.size()){
			ui->resultText->append("Удаленные ветви реестра:");
			for(int i = 0; i < rc.deletedHives.size(); i++){
				ui->resultText->append(rc.deletedHives[i].getRegPath());
			}
			ui->resultText->append("");
		}

		if(rc.changedDefaultValues.size()){
			ui->resultText->append("Ветви с измененными дефолтными значениями:");
			for(int i = 0; i < rc.changedDefaultValues.size(); i++){
				ui->resultText->append(rc.changedDefaultValues[i].getRegPath());
				ui->resultText->append(rc.changedDefaultValues[i].getDefaultValue());
			}
			ui->resultText->append("");
		}

		if(rc.changedKeys.size()){
			ui->resultText->append("Ветви с измененными значениями:");
			for(int i = 0; i < rc.changedKeys.size(); i++){
				ui->resultText->append(rc.changedKeys[i].getRegPath());
				for(int j = 0; j < rc.changedKeys[i].getDataSize(); j++)
					ui->resultText->append(rc.changedKeys[i].getData(j));
			}
			ui->resultText->append("");
		}

		if(rc.renamedKeys.size()){
			ui->resultText->append("Переименованные ключи:");
			for(int i = 0; i < rc.renamedKeys.size(); i++){
				ui->resultText->append(rc.renamedKeys[i].getRegPath());
			}
			ui->resultText->append("");
		}
	}
	else{
		if(!ui->lineEditFile1->text().size()){
			ui->resultText->append("Выберите файл 1");
		}
		if(!ui->lineEditFile2->text().size()){
			ui->resultText->append("Выберите файл 2");
		}
	}
}
