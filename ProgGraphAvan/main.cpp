#include "mainwindow.h"

#include <QApplication>
#include <QtDebug>

int main(int argc, char *argv[])
{
    qDebug("Starting...\n");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
