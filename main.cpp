#include "mainwindow.h"
#include <QApplication>
#include "splashscreen.h"
#include "autosavethread.h"

MainWindow* point_w = nullptr;

void showSplashScreen(QApplication& app);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AutoSaveThread autoSaveThread;
    autoSaveThread.start();
    MainWindow w;
    point_w = &w;
    showSplashScreen(a);
    //w.show();

    return a.exec();
}

void showSplashScreen(QApplication& app)
{
    SplashScreen splashScreen;
    splashScreen.showScreen(app);
}
