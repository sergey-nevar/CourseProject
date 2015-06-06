#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
	ui->setupUi(this);
	monitor = new MonitorWidget();
	comparisonWidget = new ComparisonWidget();
	exportWidget = new RegistryExportWidget();
	ui->mainLayout->addWidget(exportWidget);
	ui->mainLayout->addWidget(monitor);
	ui->mainLayout->addWidget(comparisonWidget);
	connect(monitor, SIGNAL(stopThread()),
			this, SLOT(stopThread()));
	connect(monitor, SIGNAL(startThread()),
			this, SLOT(startMonitoring()));
	comparisonWidget->hide();
	exportWidget->hide();
	QWidget *g = new QWidget;
	g->setLayout(ui->mainLayout);
	setCentralWidget(g);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_action_triggered(){
	monitor->hide();
	exportWidget->hide();
	comparisonWidget->show();
}

void MainWindow::on_action_2_triggered(){
	comparisonWidget->hide();
	exportWidget->hide();
	monitor->show();
	emit startThread();
}

void MainWindow::stopThread(){
	emit closeWindow();
}

void MainWindow::on_makeExport_triggered(){
	comparisonWidget->hide();
	monitor->hide();
	exportWidget->show();
}

void MainWindow::startMonitoring(){
	emit startThread();
}
