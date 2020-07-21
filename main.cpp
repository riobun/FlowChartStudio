#include "mainwindow.h"
#include <QApplication>
#include "rectangle.h"
#include "diamond.h"
#define DEBUG
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
