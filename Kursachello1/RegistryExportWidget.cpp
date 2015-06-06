#include "RegistryExportWidget.h"
#include "ui_RegistryExportWidget.h"

RegistryExportWidget::RegistryExportWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::RegistryExportWidget){
	ui->setupUi(this);
	setLayout(ui->mainLayout);
	ui->registryTree->setHeaderLabel("Ветви реестра");
	QList<QTreeWidgetItem *> rootHivesItems;
	for(int i = 0; i < 5; i++)
		rootHivesItems.append(new QTreeWidgetItem());
	rootHivesItems[0]->setText(0, "HKEY_CLASSES_ROOT");
	rootHivesItems[1]->setText(0, "HKEY_CURRENT_USER");
	rootHivesItems[2]->setText(0, "HKEY_LOCAL_MACHINE");
	rootHivesItems[3]->setText(0, "HKEY_USERS");
	rootHivesItems[4]->setText(0, "HKEY_CURRENT_CONFIG");
	for(int i = 0; i < 5; i++){
		rootHivesItems[i]->addChild(new QTreeWidgetItem());
		ui->registryTree->addTopLevelItem(rootHivesItems[i]);
	}
	connect(ui->registryTree, SIGNAL(itemExpanded(QTreeWidgetItem*)),
			this, SLOT(addSubHives(QTreeWidgetItem*)));
}

RegistryExportWidget::~RegistryExportWidget()
{
	delete ui;
}

void RegistryExportWidget::addSubHives(QTreeWidgetItem *item){
	QTreeWidgetItem *buf;
	while(item->childCount()){
		buf = item->child(0);
		item->removeChild(buf);
	}
	QString path = getHivePath(item);
	QSettings settings(path, QSettings::NativeFormat);
	QStringList keys = settings.childGroups();
	QStringList bufKeys;
	for(int i = 0, size = keys.size(); i < size; i++){
		item->addChild(new QTreeWidgetItem());
		item->child(i)->setText(0, keys[i]);
		QSettings bufSettings(getHivePath(item->child(i)), QSettings::NativeFormat);
		bufKeys = bufSettings.childGroups();
		if(bufKeys.size())
			item->child(i)->addChild(new QTreeWidgetItem());
	}
	free(buf);
}

QString RegistryExportWidget::getHivePath(QTreeWidgetItem *item){
	QTreeWidgetItem *bufItem = item;
	QStringList list;
	QString path;
	list.append(bufItem->text(0));
	while(true){
		bufItem = bufItem->parent();
		if(!bufItem)
			break;
		list.append(bufItem->text(0));
	}
	for(int i = list.size()-1; i >=0; i--){
		path += list[i];
		if(i) path += "\\";
	}
	free(bufItem);
	return path;
}

void RegistryExportWidget::on_exportButton_clicked(){
	QString pathOfBranch = getHivePath(ui->registryTree->currentItem());

	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	cif.dwFlags = STARTF_USESHOWWINDOW;
	cif.wShowWindow = SW_HIDE;
	PROCESS_INFORMATION pi;
	QString regCommand = "C:\\Windows\\System32\\reg.exe";

	QDir directory(QApplication::applicationDirPath());
	directory.cd("Snapshots");
	QStringList tmpList = pathOfBranch.split("\\");
	QString fileName = tmpList[tmpList.size()-1];
	if(tmpList[tmpList.size()-1].size() < 210)
		fileName += '_' + QDate::currentDate().toString(Qt::ISODate);
	if(tmpList[tmpList.size()-1].size() < 210)
		fileName += '(' + tmpList[0] + ')';
	QFileInfoList fileList = directory.entryInfoList();
	int i = 0;
	while(i < fileList.size()){
		if(fileList[i].isFile() && fileList[i].baseName() == fileName){
			while(fileList[i].baseName() == fileName){
				if(fileName.size()<255)
					fileName += QString("%1").arg(rand()%10);
				else{
					fileName.clear();
					for(int j = 0; j < 255; j++)
						fileName += QString("%1").arg(rand()%10);
				}
			}
			i = 0;
		}
		else
			i++;
	}

	QString commandExport = "REG EXPORT ";
	QString fileDir = directory.absolutePath() + "/" + fileName +".reg";
	QString command = commandExport + pathOfBranch+ ' ' + fileDir;
	wchar_t *wCommand = (wchar_t*)command.utf16();

	CreateProcess(regCommand.toStdWString().c_str(), wCommand,
		NULL, NULL, FALSE, NULL, NULL, NULL, &cif,&pi);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}
