#include "mainwindow.h"
#include <QApplication>
#include <regCompare.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    RegCompare rc;
    rc.compareShots("C:\\reg5.reg", "C:\\reg6.reg");
    return a.exec();
}
