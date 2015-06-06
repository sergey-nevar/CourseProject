#include "MonitorWidget.h"
#include "ui_MonitorWidget.h"

MonitorWidget::MonitorWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MonitorWidget){
	ui->setupUi(this);
	setLayout(ui->mainLayout);
}

MonitorWidget::~MonitorWidget(){
	delete ui;
}

void MonitorWidget::setResText(QString resStr){
	ui->resultText->append(resStr);

	QDir directory(QApplication::applicationDirPath());
	directory.cd("Logs");

	QString path = directory.absolutePath()+ "/" + QDate::currentDate().toString(Qt::SystemLocaleShortDate) +".txt";
	QFile logFile(path);
	if(!logFile.exists())
		logFile.open(QIODevice::WriteOnly | QIODevice::Text);
	else
		logFile.open(QIODevice::Append | QIODevice::Text);

	QTextStream stream;
	stream.setDevice(&logFile);
	stream.setCodec("UTF-8");
	stream << resStr <<endl;

	logFile.close();
}

void MonitorWidget::on_clerBufButton_clicked(){
	ui->resultText->clear();
}

void MonitorWidget::on_regeditButton_clicked(){
	WinExec("regedit", SW_SHOW);
}

void MonitorWidget::on_stopButton_clicked(){
	emit stopThread();
	ui->resultText->append("Мониторинг приостановлен");
}

void MonitorWidget::on_startButton_clicked(){
	emit startThread();
	ui->resultText->append("Мониторинг запущен");
}
