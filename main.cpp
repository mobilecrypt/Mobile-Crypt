#include <QtGui/QApplication>
#include "mainwindow.h"

/****************************************************************
 *Software was written by Rashid Kratou 2012                    *
 ****************************************************************/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
