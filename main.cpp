#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QThread>

MainWindow* point_w = nullptr;

void showSplashScreen();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    point_w = &w;
    //showSplashScreen();
    w.show();

    return a.exec();
}

void showSplashScreen()
{
    QPixmap pixmap(":/images/line_planes.jpg");
    QSplashScreen splashScreen;
    splashScreen.setPixmap(pixmap);
    splashScreen.show();
    QThread::sleep(1);
}
