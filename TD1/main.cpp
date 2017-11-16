#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QtGlobal>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
